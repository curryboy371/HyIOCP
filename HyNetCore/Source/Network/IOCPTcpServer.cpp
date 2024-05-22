#include "IOCPTcpServer.h"
#ifdef X_IOCP_NETCORE
#include <ws2tcpip.h>
#include <mswsock.h>
#include "IOCPTcpSocket.h"

namespace X
{
	ITcpServer* CreateTcpServer()
	{
		return new TcpServer();
	}

}

bool X::TcpServer::Init(ILoopEvent* loop, FTcpServerCB cb)
{
	_loop = (LoopEvent*)loop;
	_cb = cb;

	std::cout << "初始化　TCPServer " << std::endl;

	return true;
}

bool X::TcpServer::Listen(const char* ip, unsigned short port)
{
	std::cout << "Listen IP:" << ip << " port:" << port << std::endl;

	// TODO 改行代码　以后完善 存在一些问题 
	if (_sock != INVALID_SOCKET)
		closesocket(_sock);

	//初始化socket
	_sock = INVALID_SOCKET;
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&addr, sizeof(addr)))
		return false;

	if (SOCKET_ERROR == listen(_sock, 5))
		return false;

	_event.sock = _sock;
	if (_loop->AssioIOCP(_sock, &_event))
	{
		std::cout << "关联IOCP成功" << __FUNCTION__ << std::endl;
	}
	else
		std::cout << "关联IOCP失败" << __FUNCTION__ << std::endl;

	// 投递IOCP监听
	PostAccept();


	return true;

}

X::TcpServer::TcpServer()
{
	_loop = nullptr;
	_sock = INVALID_SOCKET;

	_event.tcpServer = this;
	_event.type = sEvent::Type::E_TCPSERVER;
	_event.sock = INVALID_SOCKET;

	_handle.eType = sReqHandle::sReqHandleE::HANDLE_ACCEPT;
	memset(&_handle.overlapped, 0, sizeof(_handle.overlapped));
}

void X::TcpServer::OnAccept()
{
	//SOCKADDR_IN addr;
	//int addrLen = sizeof(SOCKADDR_IN);
	//SOCKET sock = accept(_sock, (sockaddr*)&addr, &addrLen);

	//// 连接成功　调用回调函数
	//_cb(nullptr);
	sockaddr* paddr1 = NULL;
	sockaddr* paddr2 = NULL;
	int tmp1 = 0;
	int tmp2 = 0;
	GetAcceptExSockaddrs(_recvBuf, _recvLen, sizeof(SOCKADDR_IN) + 16
		, sizeof(SOCKADDR_IN) + 16, &paddr1, &tmp1, &paddr2, &tmp2);

	TcpSocket* tcp = new TcpSocket();
	tcp->OnAccept(_socket, paddr2);


	_cb(tcp);

	PostAccept();
}

void X::TcpServer::PostAccept()
{

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	//WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_socket == INVALID_SOCKET)
	{

		return;
	}
	_recvLen = 0;
	if (FALSE == AcceptEx(_sock, _socket, _recvBuf, 0, sizeof(SOCKADDR_IN) + 16
		, sizeof(SOCKADDR_IN) + 16, &_recvLen, &_handle.overlapped))
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			std::cout << "ERROR " << __FUNCTION__ << std::endl;
			return;
		}
	}
	std::cout << "OK " << __FUNCTION__ << std::endl;

	return;
}

#endif // !X_SELECT_NETCORE
