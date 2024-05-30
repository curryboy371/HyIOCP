#include "pch.h"
#include "HyServerInstance.h"

#include "UserManager.h"
#include "Room.h"

std::shared_ptr<UserManager> HyServerInstance::userMgr = nullptr;
std::shared_ptr<Room> HyServerInstance::room;

HyServerInstance::HyServerInstance()
{
	DEF_LOG;
}

HyServerInstance::~HyServerInstance()
{
	DEF_LOG;
}

void HyServerInstance::InitInstance()
{
	InitManager();
	InitProtocol();


	room = std::make_shared<Room>();
	netG = std::make_shared<NetGlobal>();
}

void HyServerInstance::ReleaseInstance()
{
	ReleaseManager();

	netG.reset();
	room.reset();
}

void HyServerInstance::InitProtocol()
{
	ServerPacketHandler::Init();
}

void HyServerInstance::InitManager()
{
	userMgr = std::make_shared<UserManager>();
}

void HyServerInstance::ReleaseManager()
{
	userMgr.reset();
}

