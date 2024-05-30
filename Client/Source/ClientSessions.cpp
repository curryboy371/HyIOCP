#include "pch.h"
#include "ClientSessions.h"

void ServerSession::PostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
}

void ServerSession::PostConnect()
{
	// 연결상태 전환
	SetSessionStatus(E_SESSION_STATUS::E_CONNECT_STATUS);

	// 로그인 시도
	Protocol::CS_LOGIN loginPkt;
	loginPkt.set_user_name("test");
	loginPkt.set_passwd("1234");
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	iocpRef->Send(GetSessionRef(), sendBuffer);
}

int32 ServerSession::PostRecv(BYTE* buffer, int32 len)
{
	HySessionRef sessionRef = GetSessionRef();
	bool bret = ClientPacketHandler::HandlePacket(sessionRef, buffer, len);

	return bret ? len : 0;
}

void ServerSession::PostSend(int32 len)
{
}
