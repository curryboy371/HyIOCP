#include "pch.h"

#include "Client.h"
#include "HyNetCore.h"
#include "MyIOCP.h"


void WorkThread(std::shared_ptr<IOCPClient> iocpRef)
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


	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	// 클라이언트는 서버와 연결하기 위해 ServerSession 사용
	SessionConfig<ServerSession> sessionConfig(L"127.0.0.1", 7777, E_SESSION_TYPE::E_SESSION_C2S, 1);
	
	std::shared_ptr<IOCPClient> iocpRef = std::make_shared<IOCPClient>(sessionConfig.GetAddress(), sessionConfig.GetSessionFactory(), sessionConfig.GetMaxSessionCount());
	HyClientInstanceRef instance = std::make_shared<HyClientInstance>();
	instance->InitHyInstance();
	instance->Set_IocpRef(iocpRef);

	bool ret = iocpRef->InitIOCP();
	
	if (ret)
	{
		// lamda...
		Ginstance->Get_threadMgr()->LaunchThread([&iocpRef]()
			{
				WorkThread(iocpRef);
			}
		);
	
		// mainthread에서 input
		while (true)
		{
			//std::this_thread::sleep_for(std::chrono::seconds(2));
			//std::string input;
			//std::cin >> input;
			//
			//Protocol::CS_CHAT chatPkt;
			//chatPkt.set_msg(input.c_str());
			//SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
			//iocpRef->SendBroadcast(sendBuffer);
		}
	
		Ginstance->Get_threadMgr()->JoinThreads();
	}
	
	instance->ReleaseInstance();

	_CrtDumpMemoryLeaks();
	return 0;
}