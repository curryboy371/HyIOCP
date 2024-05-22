#include "IOCPLoopEvent.h"
#ifdef X_IOCP_NETCORE
#include "IOCPTcpServer.h"
#include "IOCPTcpSocket.h"

namespace X {
	void InitNetCore()
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		// TODO 添加异常导出库　程序崩溃生成崩溃信息

	}

	ILoopEvent* CreateLoopEvent()
	{

		return new LoopEvent();
	}
}


void X::LoopEvent::Init()
{
	_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
	if (_iocp == INVALID_HANDLE_VALUE)
	{
		std::cout << "创建完成端口失败" << std::endl;
		return;
	}
	std::cout << "创建完成端口成功" << std::endl;


}

void X::LoopEvent::LoopOnce()
{

	DWORD lpNumberOfBytesTransferred;
	void* lpCompletionKey = nullptr;
	OVERLAPPED* lpOverlapped;
	DWORD dwMilliseconds;
	BOOL bRet = GetQueuedCompletionStatus(_iocp, &lpNumberOfBytesTransferred
		, (PULONG_PTR)&lpCompletionKey, &lpOverlapped, 0);

	if (!bRet && lpOverlapped)
	{
		return;
	}
	if (lpCompletionKey == nullptr) return;

	sEvent* event = (sEvent*)lpCompletionKey;

	switch (event->type)
	{
	case sEvent::Type::E_TCPSERVER:
		event->tcpServer->OnAccept();
		break;
	case sEvent::Type::E_TCPSOCKET:
		event->tcpSocket->OnNetMsg((sReqHandle*)lpOverlapped, bRet, lpNumberOfBytesTransferred);
		break;
	case sEvent::Type::PCK_SOCKET_CLOSE:
		event->tcpSocket->OnClose();
		break;
	default:
		break;

	}
}

void X::LoopEvent::UnInit()
{
}

void X::LoopEvent::AddEvent(sEvent* event)
{
	std::cout << "添加　事件" << event->sock
		<< " type:" << (int)event->type
		<< " ptr:" << event->tcpServer
		<< std::endl;
	_events.insert(std::pair<SOCKET, sEvent*>(event->sock, event));
}


bool X::LoopEvent::AssioIOCP(SOCKET sock, void* ptr)
{

	return _iocp == CreateIoCompletionPort((HANDLE)sock, _iocp, (ULONG_PTR)ptr, 0);
}


void X::LoopEvent::PostMsg(sEvent::Type eKey, void* pData)
{
	sEvent* event = new sEvent();
	event->type = eKey;
	event->ptr = pData;

	if (PostQueuedCompletionStatus(_iocp, 0, (ULONG_PTR)event, (LPOVERLAPPED)pData) != 0)
		std::cout << "消息发布成功" << std::endl;
}

#endif // !X_SELECT_NETCORE
