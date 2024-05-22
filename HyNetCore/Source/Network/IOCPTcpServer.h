#include "HyNetCore.h"
#include "IOCPLoopEvent.h"

#ifdef X_IOCP_NETCORE

#ifndef X_TCP_SERVER_H_
#define X_TCP_SERVER_H_

namespace X {
	class TcpServer :public ITcpServer
	{
	private:
		LoopEvent* _loop;
		FTcpServerCB _cb;
		SOCKET _sock;
		sEvent _event;
		sReqHandle _handle;

		SOCKET	_socket;
		char _recvBuf[1024];
		DWORD _recvLen;
	public:
		bool Init(ILoopEvent* loop, FTcpServerCB cb) override;


		bool Listen(const char* ip, unsigned short port) override;

	public:
		TcpServer();
		void OnAccept();
	private:
		void PostAccept();

	};


}

#endif // !_ILOOPEVENT_H_
#endif // !X_SELECT_NETCORE
