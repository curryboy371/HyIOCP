#pragma once

class User
{
public:
	User() {};
	~User() {};

public:
	const int64 GetUserID() { return user_info.id(); }
	void SetUserID(const int64& inID) { user_info.set_id(inID); }

	GETTER(HySessionRef, ownerSession);

	SETTER(HySessionRef, ownerSession);
	SETTER(Protocol::hyps_user_info, user_info);

private:
	Protocol::hyps_user_info user_info; // 이거 풀어야함..
	HySessionRef ownerSession;
};


