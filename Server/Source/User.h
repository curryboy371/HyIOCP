#pragma once

#include "Protocol.pb.h"

class User : public std::enable_shared_from_this<User>
{
public:
	User() {};
	~User() {};

public:
	const int64 GetUserID() { return user_info.id(); }

public:
	GETTER(HySessionRef, ownerSession)
	GETTER(Protocol::hyps_user_info, user_info)
	GETTER(Protocol::hyps_object_info, player_info)


	SETTER(HySessionRef, ownerSession)
	SETTER(Protocol::hyps_user_info, user_info)
	SETTER(Protocol::hyps_object_info, player_info)


private:
	Protocol::hyps_user_info user_info; 
	Protocol::hyps_object_info player_info; 
	HySessionRef ownerSession;
};

