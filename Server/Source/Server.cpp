#include <iostream>
#include "HyNetCore.h"

#ifdef _DEBUG

#pragma comment(lib, "HyNetCore\\Debug\\HyNetCore.lib")
#else
#pragma comment(lib, "HyNetCore\\Release\\HyNetCore.lib")
#endif

namespace {

	class TcpSocket : public X::ITcpSocketCB
	{
	public:
		char buff[1024]{ 0 };

		char sendBuf[1024];
		X::ITcpSocket* iTcpSocket;
	public:


		// 通过 ITcpSocketCB 继承
		virtual bool OnRecv(int len) override
		{
			std::cout << buff << std::endl;

			OnRecv();//重新投递


			return true;
		}

		void OnRecv()
		{
			iTcpSocket->DoRecv(buff, 1024);
		}


		void OnSend()
		{
			for (int i = 0; i < 1024; i++)
				sendBuf[i] = 'a';
			iTcpSocket->DoSend(sendBuf, 1024);
		}


		virtual bool OnSend(int len) override
		{

			return true;
		}

		virtual void OnClose() override
		{

			std::cout << "客户端断开（断开回调）" << std::endl;
		}

	};

}


int main()
{
	// win socket 초기화
	X::InitNetCore();

	X::ILoopEvent* loop = X::CreateLoopEvent();
	// iocp 생성
	loop->Init();

	X::ITcpServer* server = X::CreateTcpServer();

	// loop돌릴걸 lamda로 넣었네
	server->Init(loop, [loop](X::ITcpSocket* sock) {
		std::cout << "客户端连接成功1" << std::endl;
		TcpSocket* tcp = new TcpSocket();
		sock->Init(loop, tcp);

		tcp->iTcpSocket = sock;

		tcp->OnRecv();
		tcp->OnSend();
		});


	// listen 시작
	server->Listen("0.0.0.0", 7890);

	// 루프
	while (true)
	{
		loop->LoopOnce();
	}

	return 0;
}
