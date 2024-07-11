#pragma once

#include "BaseManager.h"

class User;

class UserManager : public BaseManager
{
	DEF_MUTEX;
public:
	UserManager();
	~UserManager();

public:
	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;

public:
	bool AddUser(const Protocol::hyps_user_info& InuserInfo, HySessionRef userSession);
	bool RemoveUse(HySessionRef userSession);

	bool AddPlayerInfo(const int64& InUserID, const Protocol::hyps_object_info& InPlayerInfo);

	void Broadcast(SendBufferRef sendBuffer);
	void Broadcast(SendBufferRef sendBuffer, const int64& Inexcept_id);

public:


public:
	UserRef GetUser(const int64& userKey);

	const std::unordered_map<int64, UserRef>& GetAllUsers() { return userInfoMap; }

	GETTER(int32, PlayerCount)

private:
	std::unordered_map<int64, UserRef> userInfoMap;
	int32 PlayerCount = 0;
};

