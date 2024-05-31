#pragma once

#include "BaseManager.h"
#include "ISessionManager.h"

class SessionManager : public BaseManager, public ISessionManager
{
public:
	SessionManager();
	~SessionManager();



	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;


	// ISessionManager을(를) 통해 상속됨
	virtual bool OnAddConnectedSession(HySessionRef addSession, const bool bRetry) override;
	virtual bool OnDisconnectSession(HySessionRef sessionRef) override;
	virtual bool OnLoginSession(HySessionRef sessionRef) override;

private:
	std::shared_ptr<HySession> listenSessionRef = nullptr; // listen session
	std::unordered_map<int32, HySessionRef> sessionPool; // pool이라기보다는 연결되지 않은 세션들
	std::atomic<int32> remainSessions;


};

