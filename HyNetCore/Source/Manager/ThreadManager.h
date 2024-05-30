#pragma once


class ThreadManager
{
	DEF_MUTEX;
public:
	ThreadManager();
	~ThreadManager();

	void InitThread();
	void ReleaseThread();

	void LaunchThread(std::function<void(void)> cbFunc);
	void JoinThreads();

	static void ScheduleJobQueueWork();
	static void JobQueueWork();

public:


private:
	std::vector<std::thread> threads;
};
