#include "pch.h"
#include "SessionManager.h"

BEGIN_CLIENT

SessionManager::SessionManager()
{
	DEF_LOG;
}

SessionManager::~SessionManager()
{
	DEF_LOG;
}

void SessionManager::InitManager()
{

}

void SessionManager::ReleaseManager()
{
	ReleaseSession();
}

bool SessionManager::OnAddConnectedSession(HySessionRef addSession, const bool bRetry)
{
	USE_MULOCK;
	int index = static_cast<int>(connectedSessionMap.size()); // 서버 세션 고유 id를 사용하면 그거 가져옴
	connectedSessionMap.emplace(index, addSession); // server session 저장
	addSession->SetSessioKey(index);

	std::cout << "OnAddConnectedSession client " << std::endl;
	return true;
}

bool SessionManager::OnDisconnectSession(HySessionRef sessionRef)
{
	int32 sessionKey = sessionRef->GetSessionKey();

	if (Contains(connectedSessionMap, sessionKey) == true)
	{
		// 클라면 세션 지우기 - 서버 연결시 세션 생성

		USE_MULOCK;
		sessionRef->ClearSession();
		connectedSessionMap.erase(sessionKey);
		return true;
	}

	// error

	return true;
}

bool SessionManager::OnLoginSession(HySessionRef sessionRef)
{
	return false;
}

END_NS
