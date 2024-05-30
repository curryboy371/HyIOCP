#pragma once

/* LockGuard */
/* 
	Mutex, 그리고 동일 thread가 중복으로 lock을 접근 가능하게 하기 위해 recursive lock을 사용
*/

class LockGuard
{
public:
	explicit LockGuard(std::recursive_mutex& inlockRef)
		:lockRef(inlockRef)
	{
		while (lockRef.try_lock() == false) // lock 경합 시도
		{
			// TODO 얼마나 쉬어주는건지 불확실하여 명시적으로 변경해주는게 나을 수도 
			std::this_thread::yield();
		}

		// lock 경합 성공
		// try_lcok에서 성공시 lock 처리 lock.lock();
	}

	~LockGuard()
	{
		// class 소멸시 lock 자동 반환
		lockRef.unlock();
	}

	LockGuard(const LockGuard&) = delete;
	LockGuard& operator = (const LockGuard&) = delete;

private:
	std::recursive_mutex& lockRef;
	std::vector<std::thread> threadList;
};

