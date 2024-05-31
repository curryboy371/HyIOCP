#include "pch.h"

#include "MyIOCP.h"

#include "Room.h"


void WorkThread(std::shared_ptr<IOCPServer> iocpRef)
{
	while (true)
	{
		tlsEndTickCount = ::GetTickCount64() + 64; // 여기도 타임아웃을 설정해둔다고 보면 됨.

		iocpRef->ProcessIOCompletion(10);
		
		ThreadManager::ScheduleJobQueueWork(); // 예약된 일감 처리
		
		ThreadManager::JobQueueWork(); //타임아웃에 걸리면 글로벌 큐에 넣음
	}
}

int main()
{


	// 서버는 클라이언트와 연결하기 위해 gamesession 사용
	SessionConfig<ListenSession> listenConfig(L"127.0.0.1", 7777, E_SESSION_TYPE::E_SESSION_LISTEN, 1);
	SessionConfig<GameSession> sessionConfig(L"127.0.0.1", 7777, E_SESSION_TYPE::E_SESSION_S2C, 10);
	std::shared_ptr<IOCPServer> iocpRef = std::make_shared<IOCPServer>(sessionConfig.GetAddress(), listenConfig.GetSessionFactory(), sessionConfig.GetSessionFactory(), sessionConfig.GetMaxSessionCount());

	HyServerInstanceRef instance = std::make_shared<HyServerInstance>();
	instance->InitHyInstance();
	instance->Set_IocpRef(iocpRef);

	bool bret = iocpRef->InitIOCP(); 

	if (bret)
	{
		// lamda...
		GthreadMgr->LaunchThread([&iocpRef]()
			{
				WorkThread(iocpRef);
			}
		);

		// main thread
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(3));

			Protocol::SC_CHAT chatPkt;
			chatPkt.set_msg(u8"broadcst : ");
			auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
			Ginstance->GetRoom()->DoTimer(1, [=] { Ginstance->GetRoom()->Broadcast(sendBuffer); });
		}

		GthreadMgr->JoinThreads();
	}

	instance->ReleaseInstance();

	_CrtDumpMemoryLeaks();
	return 0;
}
