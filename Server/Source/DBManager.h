#pragma once

#include "BaseManager.h"

class DBManager : public BaseManager
{
	DEF_MUTEX;
public:
	DBManager();
	~DBManager();

public:

	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;

	void DBConnect();
	void CreateTable();
	int UserLoginCheck(const std::string& name, const std::string& pw);
	int UserTableAdd(const std::string& name, const std::string& pw);

private:
	void DBDisConnect();

private:
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;


};

