#include "IOCPTcpServer.h"
#ifdef X_IOCP_NETCORE
#include <ws2tcpip.h>
#include <mswsock.h>
#include "IOCPTcpSocket.h"

namespace X
{
	TcpSocket::TcpSocket()
	{

		_cb = nullptr;
		_loop = nullptr;
		_sock = INVALID_SOCKET;

		_bSend = false;
		_sendHandle.eType = sReqHandle::sReqHandleE::HANDLE_SEND;
		_sendHandle.ptr = this;
		memset(&_sendHandle.overlapped, 0, sizeof(_sendHandle.overlapped));

		_event.tcpSocket = this;
		_event.type = sEvent::Type::E_TCPSOCKET;

		_bRecv = false;
		_recvHandle.eType = sReqHandle::sReqHandleE::HANDLE_RECV;
		_recvHandle.ptr = this;
		memset(&_recvHandle.overlapped, 0, sizeof(_recvHandle.overlapped));

		_elinkStatus = LINK_STATUS::LS_UNINITIALIZE;
	}

	TcpSocket::~TcpSocket()
	{
		//std::cout << "释放客户端" << _sock << std::endl;
	}

	bool TcpSocket::Close()
	{
		return true;
	}

	bool TcpSocket::DoClose()
	{
		switch (_elinkStatus)
		{
		case X::LINK_STATUS::LS_UNINITIALIZE:
			break;
		case X::LINK_STATUS::LS_ESTABLISHED:
		{
			_elinkStatus = LINK_STATUS::LS_WAITCLOSE;
			shutdown(_sock, SD_BOTH);
			goto postClear;
			break;
		}
		case X::LINK_STATUS::LS_WAITCLOSE:
			goto postClear;
			break;
		case X::LINK_STATUS::LS_WAITCLEAR:
			break;
		}
	postClear:
		_elinkStatus = LINK_STATUS::LS_WAITCLEAR;
		if (_loop) //如果有IO服务则投递到IO服务中关闭
		{
			_loop->PostMsg(sEvent::Type::PCK_SOCKET_CLOSE, this);
		}
		else //没有服务则直接关闭
		{
			OnClose();
		}
		return true;
	}

	bool TcpSocket::OnClose()
	{
		closesocket(_sock);
		_sock = INVALID_SOCKET;
		if (_cb)
			_cb->OnClose();
		_elinkStatus = LINK_STATUS::LS_UNINITIALIZE;
		delete this;
		return true;
	}

	void TcpSocket::Init(ILoopEvent* loop, ITcpSocketCB* cb)
	{
		_loop = (LoopEvent*)loop;
		_cb = cb;

		_event.sock = _sock;
		_loop->AssioIOCP(_sock, &_event);
	}

	bool TcpSocket::OnAccept(SOCKET sock, SOCKADDR* in)
	{
		_sock = sock;
		_elinkStatus = LINK_STATUS::LS_ESTABLISHED;
		return true;
	}

	bool TcpSocket::OnNetMsg(sReqHandle* handle, BOOL ret, int len)
	{
		if (ret)
		{
			// TODO关闭
		}
		//if (len <= 0)
		//{
		//	// 断开连接
		//	return 0;
		//}

		switch (handle->eType)
		{
		case sReqHandle::sReqHandleE::HANDLE_RECV:
		{
			_bRecv = false;

			if (len <= 0)
			{
				// 断开连接
				DoClose();
				return 0;
			}

			_cb->OnRecv(len);
			break;
		}
		case sReqHandle::sReqHandleE::HANDLE_SEND:
		{
			_bSend = false;

			_cb->OnSend(len);
			break;
		}
		case sReqHandle::sReqHandleE::HANDLE_CONNECT:
			break;
		case sReqHandle::sReqHandleE::HANDLE_RECVFROM:
			break;
		case sReqHandle::sReqHandleE::HANDLE_SENDTO:
			break;
		default:
			break;
		}

		return true;
	}

	bool TcpSocket::DoSend(const char* buff, int len)
	{
		//TODO 判断一些错误

		if (_bSend) return false;

		_sendWsaBuf.buf = (CHAR*)buff;
		_sendWsaBuf.len = len;

		DWORD dwSend = 0;
		if (WSASend(_sock, &_sendWsaBuf, 1, &dwSend, 0, &_sendHandle.overlapped, NULL) != 0)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{

				return false;
			}
		}

		_bSend = true;
		return false;
	}

	bool TcpSocket::DoRecv(char const* buf, int len)
	{
		if (_bRecv) return false;

		// TODO判断一些失败条件

		_bRecv = true;

		_recvWSABuf.buf = (CHAR*)buf;
		_recvWSABuf.len = len;

		DWORD dwRecv = 0;
		DWORD dwFlag = 0;
		if (WSARecv(_sock, &_recvWSABuf, 1, &dwRecv, &dwFlag, &_recvHandle.overlapped, NULL) != 0)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				return false;
			}
		}

		return true;
	}
}

#endif // !X_SELECT_NETCORE
