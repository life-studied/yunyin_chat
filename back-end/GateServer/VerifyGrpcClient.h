#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include <queue>

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class RPConPool {
public:
	RPConPool(std::size_t poolsize, std::string host, std::string port);
	~RPConPool();

	void Close();
	std::unique_ptr<VarifyService::Stub> getConnection();
	void returnConnection(std::unique_ptr<VarifyService::Stub> context);

private:
	std::atomic<bool> _b_stop;
	std::size_t _pool_size;
	std::string _host;
	std::string _port;
	std::queue<std::unique_ptr<VarifyService::Stub>> _connections;
	std::mutex _mtx;
	std::condition_variable _cv;
};

class VerifyGrpcClient:public Singleton<VerifyGrpcClient>
{
	friend class Singleton<VerifyGrpcClient>;
public:

	GetVarifyRsp GetVarifyCode(std::string email);

private:

	VerifyGrpcClient();
	std::unique_ptr<RPConPool> _pool;
};

class ConnectGuard
{
public:
	ConnectGuard(std::unique_ptr<VarifyService::Stub>& stub, std::unique_ptr<RPConPool>& pool);
	~ConnectGuard();
private:
	std::unique_ptr<VarifyService::Stub>& stub_;
	std::unique_ptr<RPConPool>& pool_;
};