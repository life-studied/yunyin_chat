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
	Error_Json		= 1001,		// Json��������
	RPCFailed		= 1002,		// RPC�������
	VarifyExpired	= 1003,		// ��֤���ȡʧ��
	VarifyCodeErr	= 1004,		// ��֤�����δ��Ӧ��
	UserExist		= 1005,		// ע���û��Ѵ���
};

