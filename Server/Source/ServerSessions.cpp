#include "pch.h"
#include "ServerSessions.h"

#include "HyServerInstance.h"
#include "SessionManager.h"

#include "MyIOCP.h"

ListenSession::ListenSession(E_SESSION_TYPE inSessionType)
	:HySession(inSessionType)
{

}

ListenSession::~ListenSession()
{
	std::cout << "~ListenSession" << std::endl;

}

void ListenSession::OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
	//sessionRef : clientSession

	// Accept 승인

	//SetSockOpt(socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, listenSocket);
	// socket 옵션 listeten sockt과 동일하게...

	// 서버 세션 넣어
	if (false == IOCP::SetSockOpt(sessionRef->GetSocketRef(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, GetSocketRef()))
	{
		return;

	}

	SOCKADDR_IN sockAddress;
	int sizeOfSockAddr = sizeof(sockAddress);
	if (SOCKET_ERROR == ::getpeername(sessionRef->GetSocketRef(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeOfSockAddr))
	{
		return;
	}

	//sessionRef->SetNetAddress(NetAddress(sockAddress));

	// 세션 연결상태 변경 - listen server
	SetSessionStatus(E_SESSION_STATUS::E_CONNECT_STATUS);
}

void ListenSession::OnPostConnect()
{
}

int32 ListenSession::OnPostRecv(BYTE* buffer, int32 len)
{
	return int32();
}

void ListenSession::PostSend(int32 len)
{
}

void ListenSession::OnPostDisconnect()
{
}

GameSession::GameSession(E_SESSION_TYPE inSessionType)
	:HySession(inSessionType)
{


}

GameSession::~GameSession()
{
	std::cout << "~GameSession" << std::endl;
}

void GameSession::OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
	// GameSession 연결 상태 변경
	SetSessionStatus(E_SESSION_STATUS::E_CONNECT_STATUS);
}

void GameSession::OnPostConnect()
{
}

int32 GameSession::OnPostRecv(BYTE* buffer, int32 len)
{
	HySessionRef sessionRef = GetSessionRef();
	bool bret = ServerPacketHandler::HandlePacket(sessionRef, buffer, len);
	
	return bret ? len : 0;
}

void GameSession::PostSend(int32 len)
{


}

void GameSession::OnPostDisconnect()
{
	bool bret = Ginstance->GetManager<SessionManager>()->OnDisconnectSession(shared_from_this());

	if (bret)
	{
		bool bIsRetry = true;
		Ginstance->Get_IocpRef()->Accept(shared_from_this(), bIsRetry);
	}
}
