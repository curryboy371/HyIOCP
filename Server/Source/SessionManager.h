#pragma once

#include "BaseManager.h"

class SessionManager : public BaseManager
{
public:
	SessionManager();
	~SessionManager();



	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;


private:
	std::atomic<int> sessionID;
	std::unordered_map<int, std::shared_ptr<HySession>> conSessionMap; // login된 세션 모음

	std::shared_ptr<HySession> listenSessionRef = nullptr; // listen session
	std::unordered_map<int32, HySessionRef> sessionPool; // pool이라기보다는 연결되지 않은 세션들
	std::atomic<int32> remainSessions; // sessionPool에 남은 session 수
};

