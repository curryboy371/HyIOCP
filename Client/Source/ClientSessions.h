#pragma once

#include "HySession.h"

class ServerSession : public HySession
{
public:
	ServerSession(E_SESSION_TYPE inSessionType)
		:HySession(inSessionType)
	{

	}
	~ServerSession()
	{
		std::cout << "ServerSession::~ServerSession " << std::endl;
	}
public:

	// HySession을(를) 통해 상속됨
	virtual void PostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef) override;

	virtual void PostConnect() override;

	virtual int32 PostRecv(BYTE* buffer, int32 len) override;

	virtual void PostSend(int32 len) override;

};


