#include "pch.h"
#include "ClientSessions.h"
#include "HyClientInstance.h"
#include "UserManager.h"
#include "SessionManager.h"
#include "NetworkManager.h"

void ServerSession::OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
}

void ServerSession::OnPostConnect()
{
	GCinstance->GetManager<Client::SessionManager>()->OnAddConnectedSession(shared_from_this(), false);

	// 연결상태 전환
	SetSessionStatus(E_SESSION_STATUS::E_CONNECT_STATUS);

	// 로그인 시도
	if (GCinstance->Get_bIsDevMode() == true)
	{
		GCinstance->GetManager<NetworkManager>()->Send_CS_LOGIN(shared_from_this(), "", "", [](int32 result){});
	}
	else
	{
		// 직접 로그인 시도...
		GCinstance->GetManager<NetworkManager>()->Set_mySession(shared_from_this());

	}

	
	StartRecv();
}

int32 ServerSession::OnPostRecv(BYTE* buffer, int32 len)
{
	HySessionRef sessionRef = GetSessionRef();
	bool bret = ClientPacketHandler::HandlePacket(sessionRef, buffer, len);
	return bret ? len : 0;
}

void ServerSession::PostSend(int32 len)
{
}

void ServerSession::OnPostDisconnect()
{
	
	bool bret = Ginstance->Get_isessionMgr()->OnDisconnectSession(shared_from_this());
}
