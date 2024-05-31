#include "Netpch.h"
#include "HyInstance.h"

#include "BaseManager.h"
#include "JobManager.h"
#include "ThreadManager.h"
#include "ISessionManager.h"
#include "SendBuffer.h"

std::shared_ptr<class ISessionManager> GisessionMgr;

//class ISessionManager* GisessionMgr;

JobManagerRef GjobMgr;
ThreadManagerRef GthreadMgr;
SendBufferManagerRef GsendBufferMgr;

//class HyInstance* Ginstance;

HyInstance::HyInstance(E_CORE_CONNECT Incore_connect)
	:core_connect(Incore_connect)
{
	DEF_LOG;
}

HyInstance::~HyInstance()
{
	DEF_LOG;
}

void HyInstance::InitGInstance()
{
	GjobMgr = std::make_shared<JobManager>();
	GthreadMgr = std::make_shared<ThreadManager>();
	GsendBufferMgr = std::make_shared<SendBufferManager>();
}
void HyInstance::ReleaseGInstance()
{
	GjobMgr.reset();
	GthreadMgr.reset();
	GsendBufferMgr.reset();


	// 프로토버프 종료 ( crtdebug에서 leak mem이 남아서..)
	google::protobuf::ShutdownProtobufLibrary();
}


void HyInstance::ReleaseManager()
{
	for (auto& manager : managers)
	{
		manager->ReleaseManager();
	}

	managers.clear();
}
