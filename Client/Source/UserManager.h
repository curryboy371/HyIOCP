#pragma once

#include "BaseManager.h"


BEGIN_CLIENT

class User;

class UserManager : public BaseManager
{
public:
	UserManager();
	~UserManager();

public:
	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;

public:
	SETTER(UserRef, myUser);
	GETTER(UserRef, myUser);

private:
	UserRef myUser;

};

END_CLIENT