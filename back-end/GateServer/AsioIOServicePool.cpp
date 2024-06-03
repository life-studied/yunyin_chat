#include "AsioIOServicePool.h"

AsioIOServicePool::~AsioIOServicePool()
{
	Stop();
	std::cout << "AsioIOServicePool destruct." << std::endl;
}

AsioIOServicePool::AsioIOServicePool(std::size_t size) :_io_servers(size), _works(size), _next_io_service_idx(0)
{
	for (std::size_t i = 0; i < size; i++)
	{
		_works[i] = std::make_unique<Work>(_io_servers[i]);
		_threads.emplace_back([this, i]() {
			_io_servers[i].run();
			}
		);
	}

	
}

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto& service = _io_servers[_next_io_service_idx++];
	_next_io_service_idx %= _io_servers.size();
	return service;
}

void AsioIOServicePool::Stop()
{
	for (auto& work : _works)
	{
		work->get_io_context().stop();
		work.reset();
	}

	for (auto& t : _threads)
	{
		t.join();
	}
}

