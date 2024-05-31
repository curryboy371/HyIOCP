#pragma once

#include "HySession.h"

/*
	리슨서버 세션
	오직 서버만 보유
*/

class ListenSession : public HySession
{
public:
	ListenSession() = delete;
	ListenSession(E_SESSION_TYPE inSessionType);
	~ListenSession();

public:
	// HySession을(를) 통해 상속됨
	virtual void OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef) override;

	virtual void OnPostConnect() override;

	virtual int32 OnPostRecv(BYTE* buffer, int32 len) override;

	virtual void PostSend(int32 len) override;

	virtual void OnPostDisconnect() override;

};


/*
	게임서버 세션
	클라이언트가 서버의 세션으로 보유
*/
class GameSession : public HySession
{
public:
	GameSession() = delete;
	GameSession(E_SESSION_TYPE inSessionType);
	~GameSession();

public:


	// HySession을(를) 통해 상속됨
	virtual void OnPostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef) override;

	virtual void OnPostConnect() override;

	virtual int32 OnPostRecv(BYTE* buffer, int32 len) override;

	virtual void PostSend(int32 len) override;

public:


	// HySession을(를) 통해 상속됨
	virtual void OnPostDisconnect() override;

};

