#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"

RPConPool::RPConPool(std::size_t poolsize, std::string host, std::string port) : _pool_size(poolsize), _host(host), _port(port), _b_stop(false)
{
	for (std::size_t i = 0; i < _pool_size; i++)
	{
		std::shared_ptr<Channel> channel = grpc::CreateChannel(_host+":"+_port, grpc::InsecureChannelCredentials());
		_connections.push(VarifyService::NewStub(channel));
	}
}

RPConPool::~RPConPool()
{
	std::scoped_lock<std::mutex> lock(_mtx);
	Close();
	while (!_connections.empty())
	{
		_connections.pop();
	}
}

void RPConPool::Close()
{
	_b_stop = true;
	_cv.notify_all();
}

std::unique_ptr<VarifyService::Stub> RPConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mtx);
	_cv.wait(lock, [this]() {
		if (_b_stop) return true;
		
		return !_connections.empty();
		}
	);

	if (_b_stop)	return nullptr;

	auto context = std::move(_connections.front());
	_connections.pop();
	return context;
}

void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> context)
{
	std::scoped_lock<std::mutex> lock(_mtx);
	if (_b_stop)	return;

	_connections.push(std::move(context));
	_cv.notify_one();
}

GetVarifyRsp VerifyGrpcClient::GetVarifyCode(std::string email)
{
	ClientContext context;
	GetVarifyRsp reply;
	GetVarifyReq request;
	request.set_email(email);
	auto stub = _pool->getConnection();
	Status status = stub->GetVarifyCode(&context, request, &reply);

	if (status.ok()) {
		_pool->returnConnection(std::move(stub));
		return reply;
	}
	else {
		reply.set_error(ErrorCodes::RPCFailed);
		_pool->returnConnection(std::move(stub));
		return reply;
	}
}

VerifyGrpcClient::VerifyGrpcClient()
{
	auto& config_mgr = ConfigMgr::GetInstance();
	std::string host = config_mgr["VarifyServer"]["Host"];
	std::string port = config_mgr["VarifyServer"]["Port"];
	_pool.reset(new RPConPool(5, host, port));
}
