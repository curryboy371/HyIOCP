#pragma once

#include "LockQueue.h"
#include "JobManager.h"
#include "JobScheduler.h"

// std 함수 포인터 & 람다를 사용하여 callback  job 만듦
using CBJob = std::function<void()>;
class Job
{
public:
	Job(CBJob&& InCB)
		:CB(std::move(InCB))
	{

	}

	template<typename T, typename Ret, typename... Args>
	Job(std::shared_ptr<T> owner, Ret(T::* memFunc)(Args...), Args&&... args)
	{
		CB = [owner, memFunc, args...]()
		{
			(owner.get()->*memFunc)(args...);
		};
	}

	void Excute()
	{
		CB();
	}

private:
	CBJob CB;
};



class JobQueue : public std::enable_shared_from_this<JobQueue>
{
public:
	void DoAsync(CBJob&& InCB)
	{
		Push(std::make_shared<Job>(std::move(InCB)));
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::* memFunc)(Args...), Args... args)
	{
		std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
		Push(std::make_shared<Job>(owner, memFunc, std::forward<Args>(args)...));
	}

	void DoTimer(uint64 afterTick, CBJob&& callback)
	{
		JobRef jobRef = std::make_shared<Job>(std::move(callback));
		JobQueueRef temp = shared_from_this();

		Ginstance->Get_jobMgr()->Get_jobSchedulerRef()->Reservc(afterTick, shared_from_this(), jobRef);
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(uint64 afterTick, Ret(T::* memFunc)(Args...), Args... args)
	{
		std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
		JobRef jobRef = std::make_shared<Job>(owner, memFunc, std::forward<Args>(args)...);
		Ginstance->Get_jobMgr()->Get_jobSchedulerRef()->Reservc(afterTick, owner, jobRef);
	}

	void ClearJobs() { jobs.Clear(); }

public:
	void Excute();
	void Push(JobRef job, bool pushOnly = false);

	virtual void FlushJob();

protected:
	LockQueue<JobRef> jobs;
	std::atomic<int32> jobCount = 0;

private:

};

