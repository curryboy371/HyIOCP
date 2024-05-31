#include "Netpch.h"
#include "HyInstance.h"

#include "BaseManager.h"
#include "JobManager.h"
#include "ThreadManager.h"
#include "ISessionManager.h"
#include "SendBuffer.h"


HyInstanceRef Ginstance;




HyInstance::HyInstance(E_CORE_CONNECT Incore_connect)
	:core_connect(Incore_connect)
{
	LOG_FUNC;
}

HyInstance::~HyInstance()
{
	LOG_FUNC;
}

void HyInstance::InitGInstance()
{
	isessionMgr.reset();

	jobMgr = std::make_shared<JobManager>();
	threadMgr = std::make_shared<ThreadManager>();
	sendBufferMgr = std::make_shared<SendBufferManager>();
}
void HyInstance::ReleaseGInstance()
{
	Ginstance.reset();

	jobMgr.reset();
	threadMgr.reset();
	sendBufferMgr.reset();

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
