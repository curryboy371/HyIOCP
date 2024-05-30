#pragma once

#include "BaseManager.h"

class SessionManager : public BaseManager
{
public:
	SessionManager();
	~SessionManager();

private:


	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;

	virtual void ReleaseManager() override;

};

