#include "Netpch.h"
#include "JobScheduler.h"

void JobScheduler::Reservc(uint64 tickAfter, std::weak_ptr<JobQueue> owner, JobRef job)
{
	const uint64 tickCount = GetTickCount64();
	const uint64 excuteTick = tickCount + tickAfter;
	JobData* jobData = new JobData(owner, job);

	{
		USE_MULOCK;
		scheduledJobs.push(ScheduledJob{ excuteTick, jobData });
	}


}

void JobScheduler::Distribute(uint64 now)
{
	// 한번에 한 thread만...
	if (_distributing.exchange(true) == true)
	{
		// 이미 distributing이 true여서 실행되고 있는 경우...
		// 한번에 하나의 thread만 실행하기 위해 return
		return;
	}

	std::vector<ScheduledJob> jobs;
	{
		USE_MULOCK;

		while (scheduledJobs.empty() == false)
		{
			const ScheduledJob& timerItem = scheduledJobs.top();

			if (now < timerItem.excuteTick)
			{
				break;
			}

			jobs.push_back(timerItem);
			scheduledJobs.pop();

		}
	}


	for (ScheduledJob& job : jobs)
	{
		if (JobQueueRef owner = job.jobData->owner.lock())
		{
			bool pushOnly = true; // 실행중인 job이 없더라도 예약이므로 즉시 실행시키지 않음
			owner->Push(job.jobData->job, pushOnly);

		}
		// data 껍데기 소멸..
		delete job.jobData;
	}

	// 종료
	_distributing.store(false);

}

void JobScheduler::Clear()
{
	USE_MULOCK;

	while (scheduledJobs.empty() == false)
	{
		const ScheduledJob& timerItem = scheduledJobs.top();
		// data 껍데기 소멸..
		delete timerItem.jobData;
		scheduledJobs.pop();
	}
}
