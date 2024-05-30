#pragma once


#pragma region Global
extern class JobManager* GjobMgr;
extern class ThreadManager* GthreadMgr;
extern class SendBufferManager* GsendBufferMgr;

#pragma endregion


class NetGlobal
{
public:
	NetGlobal() final;
	~NetGlobal();
};

