#pragma once

#include "BaseManager.h"
#include "ISessionManager.h"
BEGIN_CLIENT

class SessionManager : public BaseManager, public ISessionManager
{
public:
	SessionManager();
	~SessionManager();


public:

	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;

	virtual void ReleaseManager() override;


	// ISessionManager을(를) 통해 상속됨
	virtual bool OnAddConnectedSession(HySessionRef addSession, const bool bRetry) override;

	virtual bool OnDisconnectSession(HySessionRef sessionRef) override;

	virtual bool OnLoginSession(HySessionRef sessionRef) override;

};

END_NS