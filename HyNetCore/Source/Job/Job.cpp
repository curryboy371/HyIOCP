#include "Netpch.h"
#include "Job.h"

void JobQueue::Excute()
{
	tlsCurJobQueue = this;

	while (true)
	{
		std::vector<JobRef> curjobs;
		jobs.PopAll(OUT curjobs);

		const int32 curjobCount = static_cast<int32>(curjobs.size());

		for (int32 i = 0; i < curjobCount; ++i)
		{
			curjobs[i]->Excute();
		}

		// 남은 일감이 0이면 ( 반복문을 실행하는 과정에 다른 job이 추가되지 않았다면
		if (jobCount.fetch_sub(curjobCount) == jobCount)
		{
			tlsCurJobQueue = nullptr;
			return;
		}

		// 스레드가 excute에서 너무 오래 머무른경우
		const uint64 now = ::GetTickCount64();
		if (now >= tlsEndTickCount)
		{
			tlsCurJobQueue = nullptr;

			// 여유 있는 다른 쓰레드가 실행하도록 GlobalQueue에 넘김
			GjobMgr->Push(shared_from_this());
			break;
		}

		// 그렇지 않은경우 다시 반복문 실행.
	}
}

void JobQueue::Push(JobRef job, bool pushOnly)
{
	// 순서 주의
	const int32 preCount = jobCount.fetch_add(1);
	jobs.Push(job);

	// 첫번째로 잡을 넣은 잡이면... 해당 쓰레드가 실행까지...
	if (preCount == 0)
	{
		// 이미 실행중인 JobQueue가 없으면 실행
		// 이렇게 하면 실행순서에 대한 보장은 없을 것임.
		if (tlsCurJobQueue == nullptr && pushOnly == false)
		{
			Excute();
		}
		else
		{
			// 다른 쓰레드가 실행하도록 넘김
			GjobMgr->Push(shared_from_this());
		}

	}
}

void JobQueue::FlushJob()
{
	while (true)
	{
		JobRef job = jobs.Pop();
		if (job == nullptr)
		{
			break;
		}

		job->Excute();
	}
}
