#pragma once

#include "Job.h"

class Room : public JobQueue
{
public:
	void Enter(UserRef user);
	void Leave(UserRef user);
	void Broadcast(SendBufferRef sendBuffer);

public:
	// multi thread 환경에서는 job으로 접근
	//void PushJob(JobRef job) { _jobs.Push(job); }
	virtual void FlushJob() override;

private:
	//std::recursive_mutex _mtx;
	std::map<uint64, UserRef> users;
};

