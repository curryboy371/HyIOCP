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
	bool AddClientSession(UserRef user);

	bool AddUser(const Protocol::hyps_user_info& InuserInfo, HySessionRef userSession);
	bool RemoveUse(HySessionRef userSession);

public:
	UserRef GetUser(const int64& userKey);
	UserRef GetMyUser();
	bool GetMyUsers(std::vector<UserRef>& OutUsers);

public:
	//SETTER(UserRef, myUser);
	//GETTER(UserRef, myUser);

private:
	std::vector<UserRef> myUsers;

	std::unordered_map<int64, UserRef> userInfoMap;

};
