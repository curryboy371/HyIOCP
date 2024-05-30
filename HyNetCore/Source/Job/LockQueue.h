#pragma once

template<typename T>
class LockQueue
{
	DEF_MUTEX;
public:
	void Push(T job)
	{
		USE_MULOCK;

		jobs.push(job);
	}

	T Pop()
	{
		USE_MULOCK;

		if (jobs.empty())
		{
			return T();
		}

		T ret = jobs.front();
		jobs.pop();
		return ret;
	}

	void PopAll(OUT std::vector<T>& Outjobs)
	{
		USE_MULOCK;
		while (T job = Pop())
		{
			Outjobs.push_back(job);
		}
	}
	void Clear();


private:
	std::queue<T> jobs;
};

template<typename T>
inline void LockQueue<T>::Clear()
{

}