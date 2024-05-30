#include "Netpch.h"
#include "JobManager.h"
#include "JobScheduler.h"

JobManager::JobManager()
	:jobScheduler(std::make_shared<JobScheduler>())
{

}

JobManager::~JobManager()
{
	jobScheduler.reset();
}

void JobManager::Push(JobQueueRef jobQueue)
{
	jobQueues.Push(jobQueue);
}

JobQueueRef JobManager::Pop()
{
	return jobQueues.Pop();
}
