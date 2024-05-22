#include "HyNetCore.h"
#include "IOCPLoopEvent.h"

#ifdef X_IOCP_NETCORE

#ifndef X_TCP_SOCKET_H_
#define X_TCP_SOCKET_H_

namespace X {
	//记录客户端当前的状态
	enum class LINK_STATUS
	{
		LS_UNINITIALIZE = 0, // 无效状态
		LS_ESTABLISHED,  // 连接状态
		LS_WAITCLOSE,    // 等待关闭状态
		LS_WAITCLEAR,    // 等待清除状态
	};

	class TcpSocket :public ITcpSocket
	{
	private:
		LoopEvent* _loop;
		ITcpSocketCB* _cb;
		SOCKET _sock;

		sEvent _event;

		//发送缓冲区
		bool _bSend;
		WSABUF _sendWsaBuf;
		sReqHandle _sendHandle;

		//接收缓冲区
		bool _bRecv;
		WSABUF _recvWSABuf;
		sReqHandle _recvHandle;

		//当前状态
		LINK_STATUS _elinkStatus;
	public:
		TcpSocket();

		~TcpSocket();
	public:
		bool OnAccept(SOCKET sock, SOCKADDR* in);

		bool OnNetMsg(sReqHandle* handle, BOOL ret, int len);

		//关闭客户端
		bool OnClose();

		//准备关闭客户端
		bool DoClose();
	public:
		// 通过 ITcpSocket 继承
		virtual void Init(ILoopEvent* loop, ITcpSocketCB* cb) override;

		virtual bool DoSend(const char* buff, int len) override;

		virtual bool DoRecv(char const* buff, int len) override;

		//主动关闭客户端
		virtual bool Close() override;
	};
}

#endif // !_ILOOPEVENT_H_

#endif // !X_SELECT_NETCORE
