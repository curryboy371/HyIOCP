#pragma once

#include "Job.h"

// 한 스레드가 너무 오래 job을 실행하게 두지 않도록
// Job Manager가 전역 queue를 두고 관리
// queue에 push, pop은 싱글 스레드처럼 동작하지만, 해당 함수 내부에서 multi thread에서 lock을 잡게 동작함.
// 따라서 멀티스레드 환경에서 안전할 것임.

class JobManager
{
public:
	JobManager();
	~JobManager();

public:
	void Push(JobQueueRef jobQueue);
	JobQueueRef Pop();

	GETTER(JobSchedulerRef, jobScheduler)


private:
	LockQueue<JobQueueRef> jobQueues; // 실행되지 못한 Job은 여기서 관리함

	JobSchedulerRef jobScheduler;
};