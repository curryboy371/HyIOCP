#include "pch.h"
#include "HyClientInstance.h"

#include "UserManager.h"
//#include "Room.h"

std::shared_ptr<UserManager> HyClientInstance::userMgr = nullptr;
//std::shared_ptr<Room> HyServerInstance::room;

HyClientInstance::HyClientInstance()
{
	DEF_LOG;
}

HyClientInstance::~HyClientInstance()
{
	DEF_LOG;
}

void HyClientInstance::InitInstance()
{
	InitManager();
	InitProtocol();


	//room = std::make_shared<Room>();
	netG = std::make_shared<NetGlobal>();
}

void HyClientInstance::ReleaseInstance()
{
	ReleaseManager();

	netG.reset();
	//room.reset();
}

void HyClientInstance::InitProtocol()
{
	ClientPacketHandler::Init();
}

void HyClientInstance::InitManager()
{
	userMgr = std::make_shared<UserManager>();
}

void HyClientInstance::ReleaseManager()
{
	userMgr.reset();
}

