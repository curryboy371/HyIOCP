#include "Netpch.h"
#include "HyInstance.h"

#include "BaseManager.h"
#include "JobManager.h"
#include "ThreadManager.h"
#include "SendBuffer.h"

JobManagerRef GjobMgr;
ThreadManagerRef GthreadMgr;
SendBufferManagerRef GsendBufferMgr;

//class HyInstance* Ginstance;

HyInstance::HyInstance()
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
}


void HyInstance::ReleaseManager()
{
	for (auto& manager : managers)
	{
		manager->ReleaseManager();
	}

	managers.clear();
}

