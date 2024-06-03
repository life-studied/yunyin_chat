#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {

}

void CServer::Start()
{	
	auto self = shared_from_this();
	auto& ioc = AsioIOServicePool::GetInstance()->GetIOService();
	auto new_conn = std::make_shared<HttpConnection>(ioc);

	_acceptor.async_accept(new_conn->GetSocket(), [self, new_conn](beast::error_code ec) {
		try {
			//出错则放弃这个连接，继续监听新链接
			if (ec) {
				self->Start();
				return;
			}

			//处理新链接，创建HpptConnection类管理新连接
			new_conn->Start();
			//继续监听
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
	});
}


