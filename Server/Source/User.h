#pragma once

#include "Protocol.pb.h"

class User
{
public:
	User() {};
	~User() {};

public:
	const int64 GetUserID() { return user_info.id(); }

public:
	GETTER(HySessionRef, ownerSession);
	GETTER(Protocol::hyps_user_info, user_info);


	SETTER(HySessionRef, ownerSession);
	SETTER(Protocol::hyps_user_info, user_info);


private:
	Protocol::hyps_user_info user_info; // 이거 풀어야함..
	HySessionRef ownerSession;
};

