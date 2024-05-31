#pragma once

/* 
 Core에서 SessionManager와 중간에 연결하기 위해 사용할
  Session Manager의 insterace class

  SessionManger는 ISession과 BaseMgr을 다중상속하고
	ISession은 shared_ptr 안쓰고
	Base에서는 shared_ptr 사용

*/
class ISessionManager
{
	DEF_MUTEX
public:
	ISessionManager() {};
	virtual ~ISessionManager() {};

	void ReleaseSession();
	

	virtual bool OnAddConnectedSession(HySessionRef addSession, const bool bRetry) abstract;
	virtual bool OnDisconnectSession(HySessionRef sessionRef) abstract;
	virtual bool OnLoginSession(HySessionRef sessionRef) abstract;

public:
	SETTER(HySessionRef, listenSession);
	GETTER(HySessionRef, listenSession)

protected:
	std::atomic<int> sessionID;
	std::unordered_map<int64, HySessionRef> connectedSessionMap;
	HySessionRef listenSession;
};

