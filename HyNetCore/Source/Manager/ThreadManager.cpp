#include "Netpch.h"

#include "ThreadManager.h"

ThreadManager::ThreadManager()
{


}

ThreadManager::~ThreadManager()
{


}

void ThreadManager::InitThread()
{
}

void ThreadManager::ReleaseThread()
{
}

void ThreadManager::LaunchThread(std::function<void(void)> cbFunc)
{
	// lock
	USE_MULOCK;

	// callback 함수와 함께 thread vector에 push
	threads.push_back(std::thread(
		[cbFunc, this]() -> void
		{
			InitThread();
			cbFunc(); // callback Fucntion
			ReleaseThread();

		}
	));
}

void ThreadManager::JoinThreads()
{

	for (auto& trd : threads)
	{
		trd.join();
	}

	threads.clear();
}

void ThreadManager::ScheduleJobQueueWork()
{
	const uint64 now = ::GetTickCount64();
	Ginstance->Get_jobMgr()->Get_jobSchedulerRef()->Distribute(now);
}

void ThreadManager::JobQueueWork()
{
	while (true)
	{
		uint64 now = ::GetTickCount64();
		if (now > tlsEndTickCount)
		{
			break;
		}

		JobQueueRef jobQueue = Ginstance->Get_jobMgr()->Pop();
		if (jobQueue == nullptr)
		{
			break;
		}

		jobQueue->Excute();

	}
}
