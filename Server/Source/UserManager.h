#pragma once

#include "BaseManager.h"

#include "Protocol.pb.h"

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

	void Broadcast(SendBufferRef sendBuffer);
public:
	UserRef GetUser(const int64& userKey);

private:
	std::unordered_map<int64, UserRef> userInfoMap;
};

