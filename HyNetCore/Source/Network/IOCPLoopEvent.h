#pragma once
#include "HyNetCore.h"

#ifdef X_IOCP_NETCORE
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <unordered_map>

#pragma comment(lib,"ws2_32")
#pragma comment(lib, "Mswsock")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "psapi")

#include <iostream>

#ifndef X_LOPEVENT_H_
#define X_LOPEVENT_H_

namespace X {
	struct sEvent
	{
		enum class Type
		{
			E_TCPSERVER,
			E_TCPSOCKET,
			PCK_ACCEPT_CLOSE,
			PCK_SOCKET_CLOSE,
			PCK_USER_DATA,	//用户投递的数据，调用DoPost让用户自己消耗
		};
		Type type;
		SOCKET sock;
		union
		{
			class TcpServer* tcpServer;
			class TcpSocket* tcpSocket;
			void* ptr;
		};
	};

	struct sReqHandle
	{
		OVERLAPPED	 overlapped;
		enum class sReqHandleE
		{
			HANDLE_ACCEPT = 0,
			HANDLE_RECV,
			HANDLE_SEND,
			HANDLE_CONNECT,
			HANDLE_RECVFROM,
			HANDLE_SENDTO,
		};
		sReqHandleE eType;//投递的类型
		void* ptr;
	};

	class LoopEvent :public ILoopEvent
	{
	private:
		std::unordered_map<SOCKET, sEvent*> _events;
		HANDLE _iocp;
	public:
		void Init() override;

		void LoopOnce() override;

		void UnInit() override;
	public:
		void AddEvent(sEvent* event);

		// 关联完成端口
		bool AssioIOCP(SOCKET sock, void* ptr);

		//消息处理
		void PostMsg(sEvent::Type eKey, void* pData);
	};

}

#endif // !_ILOOPEVENT_H_
#endif // !X_SELECT_NETCORE
