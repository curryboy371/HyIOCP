#include "Netpch.h"
#include "NetGlobal.h"

#include "JobManager.h"

#pragma region Global

JobManager* GjobMgr = nullptr;
ThreadManager* GthreadMgr = nullptr;
SendBufferManager* GsendBufferMgr = nullptr;;

#pragma endregion

NetGlobal::NetGlobal()
{
	GthreadMgr = new ThreadManager;
	GsendBufferMgr = new SendBufferManager;
	GjobMgr = new JobManager;
}

NetGlobal::~NetGlobal()
{
	delete GthreadMgr;
	delete GsendBufferMgr;
	delete GjobMgr;
}
