#pragma once

/*
	JobScheduler

	Job을 예약해서 실행하기 위한 Job

	실행순서



*/
// Job
struct JobData
{
	JobData(std::weak_ptr<class JobQueue> owner, JobRef job) : owner(owner), job(job)
	{

	}

	std::weak_ptr<class JobQueue> owner;
	JobRef job;
};

// JobData, 예약 시간 관리 구조체
class ScheduledJob
{
public:
	bool operator < (const ScheduledJob& other) const
	{
		return excuteTick > other.excuteTick;
	}

	uint64 excuteTick = 0;
	JobData* jobData = nullptr;
};

class JobScheduler
{
	DEF_MUTEX;

public:
	void Reservc(uint64 tickAfter, std::weak_ptr<JobQueue> owner, JobRef job);
	void Distribute(uint64 now);
	void Clear();

	std::priority_queue<ScheduledJob> scheduledJobs;
	std::atomic<bool> _distributing = false;
};

