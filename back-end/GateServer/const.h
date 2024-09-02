#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
	Success = 0,
	Error_Json		= 1001,		// Json解析错误
	RPCFailed		= 1002,		// RPC请求错误
	VarifyExpired	= 1003,		// 验证码获取失败
	VarifyCodeErr	= 1004,		// 验证码错误未对应上
	UserExist		= 1005,		// 注册用户已存在
};

