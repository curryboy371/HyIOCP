#include "Netpch.h"
#include "IOCPHandler.h"

#include "HySession.h"
#include "ISessionManager.h"

bool IOCPHandler::OnAccept(HySessionRef sessionRef, OverlappedEx* overlapped)
{
	if (HySessionRef listenSession = Ginstance->Get_isessionMgr()->Get_listenSession())
	{
		listenSession->OnAccept(overlapped, sessionRef); // listen server의 accpet실행
		sessionRef->OnAccept(overlapped, sessionRef);

		sessionRef->StartRecv();
	}

	return true;
}

bool IOCPHandler::OnConnect(HySessionRef sessionRef, OverlappedEx* overlapped)
{
	sessionRef->OnConnect(); // 클라 전용
	return true;
}

bool IOCPHandler::OnReceive(HySessionRef sessionRef, OverlappedEx* overlapped)
{
	sessionRef->OnRecv(overlapped);
	sessionRef->StartRecv();
	return true;
}

bool IOCPHandler::OnSend(HySessionRef sessionRef, OverlappedEx* overlapped)
{
	sessionRef->OnSend(overlapped);
	return true;
}

bool IOCPHandler::OnDisconnect(HySessionRef sessionRef, OverlappedEx* overlapped)
{
	sessionRef->OnDisconnect(); // 서버에서만 Disconnect 노티
	return true;
}
