#include "pch.h"
#include "SessionManager.h"
#include "Room.h"

SessionManager::SessionManager()
{
	LOG_FUNC;
}

SessionManager::~SessionManager()
{
	LOG_FUNC;
}

void SessionManager::InitManager()
{

}

void SessionManager::ReleaseManager()
{
	ReleaseSession();

	for (auto& pair : sessionPool)
	{
		pair.second->ClearSession();
	}

	sessionPool.clear();
	remainSessions.store(0);
}


bool SessionManager::OnAddConnectedSession(HySessionRef addSession, const bool bRetry)
{
	addSession->SetOverlappedOwner(E_IO_TYPE::E_IO_ACCEPT, addSession);

	// 기존 세션이 있으면
	if (bRetry == false)
	{
		addSession->SetSessionStatus(E_SESSION_STATUS::E_WAIT_STATUS);

		sessionID.fetch_add(1);
		sessionPool.emplace(sessionID, addSession);
		addSession->SetSessioKey(sessionID);
		remainSessions.fetch_add(1);
		return true;
	}
	else
	{
		USE_MULOCK;

		int32 sessionKey = addSession->GetSessionKey();

		if (Contains(sessionPool, sessionKey) == true)
		{
			if (!sessionPool[sessionKey])
			{
				// 세션을 세션 풀에 업데이트
				sessionPool[sessionKey] = addSession;
				connectedSessionMap.erase(sessionKey);
				remainSessions.fetch_add(1);

				// 세션 상태를 재시도 상태로 설정-그대로 써도 될 수도?
				Ginstance->Get_IocpRef()->SetupSocket((addSession->GetSocketRef()));
				addSession->SetSessionStatus(E_SESSION_STATUS::E_RETRY_STATUS);
				return true;
			}
		}

	}

	return false;

}

bool SessionManager::OnLoginSession(HySessionRef sessionRef)
{
	if (sessionRef->GetSessionStatus() == E_SESSION_STATUS::E_LOGIN_STATUS)
	{
		return true;
	}

	if (remainSessions.load() > 0)
	{
		// TODO 로그인 성공시마다 Lock 잡는거 수정 할 수 있으면 수정필요
		USE_MULOCK;

		int32 sessionKey = sessionRef->GetSessionKey();

		if (Contains(sessionPool, sessionKey) == true)
		{
			if (sessionPool[sessionKey])
			{
				if (Contains(connectedSessionMap, sessionKey) == false)
				{
					connectedSessionMap.emplace(sessionKey, sessionPool[sessionKey]);
					sessionPool[sessionKey].reset();
					remainSessions.fetch_sub(1);
					sessionRef->SetSessionStatus(E_SESSION_STATUS::E_LOGIN_STATUS);

					return true;
				}
			}
		}
	}
	else
	{
		ERR_V("remain session zero");
	}

	return false;

}

void SessionManager::BroadCast(SendBufferRef sendBuffer)
{
	for (auto session : sessionPool)
	{
		if (session.second->IsConnected())
		{
			session.second->PreSend(sendBuffer);
		}
	}

}

bool SessionManager::OnDisconnectSession(HySessionRef sessionRef)
{
	// 서버면 세션을 지우지 않고 연결 해제, 초기화. - 세션 수는 항상 동일하게 유지하도록...
	int32 sessionKey = sessionRef->GetSessionKey();
	if (Contains(connectedSessionMap, sessionKey) == true)
	{
		USE_MULOCK;

		// 유저 매니저 정리
		GSinstance->GetManager<UserManager>()->RemoveUse(sessionRef);

		// 세션을 초기화 하고 다시 Accept 상태로 변경
		sessionRef->ClearSession();

		//erase는 accept에서 한번에...

		return true;

	}
	else
	{
		//error
	}



	return false;
}
