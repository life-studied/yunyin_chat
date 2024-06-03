#pragma once
#include "Singleton.h"
#include <boost/asio.hpp>
#include <thread>


class AsioIOServicePool : public Singleton<AsioIOServicePool>
{
	friend class Singleton<AsioIOServicePool>;
public:

	using IOService = boost::asio::io_context;
	using Work = boost::asio::io_context::work;
	using WorkPtr = std::unique_ptr<Work>;

	~AsioIOServicePool();
	AsioIOServicePool(const AsioIOServicePool&) = delete;
	AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;

	boost::asio::io_context& GetIOService();

	void Stop();
private:
	AsioIOServicePool(std::size_t size = 2 /*std::thread::hardware_concurrency()*/);
	std::vector<IOService> _io_servers;
	std::vector<WorkPtr> _works;
	std::vector<std::thread> _threads;
	std::size_t _next_io_service_idx;	// idx for GetIOService, loop return
};
