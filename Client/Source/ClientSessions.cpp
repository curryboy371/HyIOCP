#include "pch.h"
#include "ClientSessions.h"
#include "HyClientInstance.h"
#include "UserManager.h"
#include "SessionManager.h"

void ServerSession::OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
}

void ServerSession::OnPostConnect()
{
	Ginstance->GetManager<Client::SessionManager>()->OnAddConnectedSession(shared_from_this(), false);

	// 연결상태 전환
	SetSessionStatus(E_SESSION_STATUS::E_CONNECT_STATUS);

	// 로그인 시도
	Protocol::CS_LOGIN loginPkt;
	loginPkt.set_user_name("test");
	loginPkt.set_passwd("1234");
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	iocpRef->Send(GetSessionRef(), sendBuffer);

	
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
	bool bret = GisessionMgr->OnDisconnectSession(shared_from_this());
}
