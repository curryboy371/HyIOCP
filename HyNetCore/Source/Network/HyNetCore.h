#pragma once
#ifndef _X_NET_CORE_H_
#define _X_NET_CORE_H_

//#define X_SELECT_NETCORE
#define X_IOCP_NETCORE

#include <functional>
namespace X {

	class ILoopEvent
	{
	public:

		virtual void Init() = 0;

		virtual void LoopOnce() = 0;

		virtual void UnInit() = 0;

		virtual ~ILoopEvent() {}

	};

	class ITcpSocketCB
	{
	public:
		virtual bool OnRecv(int len) = 0;

		virtual bool OnSend(int len) = 0;

		//客户端断开后的回调
		virtual void OnClose() = 0;

		virtual ~ITcpSocketCB() {}
	};


	class ITcpSocket
	{
	public:
		virtual void Init(ILoopEvent* loop, ITcpSocketCB* cb) = 0;

		virtual bool DoSend(const char* buff, int len) = 0;

		virtual bool DoRecv(char const* buff, int len) = 0;

		//主动关闭客户端
		virtual bool Close() = 0;

		virtual ~ITcpSocket() {}

	};


	typedef std::function<void(ITcpSocket*)> FTcpServerCB;

	class ITcpServer
	{
	public:
		//  이벤트 루프와 연결
		/// <summary>
		/// TCP 서비스를 초기화합니다.
		/// </summary>
		/// <param name="loop">이벤트 루프</param>
		/// <param name="cb">사용자가 연결에 성공한 후 콜백될 함수</param>
		/// <returns></returns>
		virtual bool Init(ILoopEvent* loop, FTcpServerCB cb) = 0;

		virtual bool Listen(const char* ip, unsigned short port) = 0;

		virtual ~ITcpServer() {}


	};


	void InitNetCore();

	ILoopEvent* CreateLoopEvent();

	ITcpServer* CreateTcpServer();

}

#endif // !_X_NET_CORE_H_
