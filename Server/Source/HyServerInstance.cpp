#include "pch.h"
#include "HyServerInstance.h"

#include "UserManager.h"
#include "SessionManager.h"
#include "Room.h"

HyServerInstanceRef Ginstance;

RoomRef Groom;

HyServerInstance::HyServerInstance()
{
	DEF_LOG;

}

HyServerInstance::~HyServerInstance()
{
	DEF_LOG;
}

void HyServerInstance::InitHyInstance()
{
	InitGInstance();
	InitProtocol();
	InitManager();
}

void HyServerInstance::ReleaseInstance()
{
	ReleaseGInstance();
	ReleaseManager();
}

void HyServerInstance::InitGInstance()
{
	HyInstance::InitGInstance();

	Ginstance = std::static_pointer_cast<HyServerInstance>(shared_from_this());
	Groom = std::make_shared<Room>();
}

void HyServerInstance::ReleaseGInstance()
{
	HyInstance::ReleaseGInstance();

	Ginstance.reset();
	Groom.reset();
	GisessionMgr.reset();
}

void HyServerInstance::ReleaseManager()
{
	HyInstance::ReleaseManager();
	
}

void HyServerInstance::InitProtocol()
{
	ServerPacketHandler::Init();
}

void HyServerInstance::InitManager()
{
	// 언리얼처럼 Reflection 기능이 있다면 하나하나 만들진 않아도 되는데..
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<UserManager>()));
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<SessionManager>()));


	for (auto& manager : managers)
	{
		manager->InitManager();
	}

	GisessionMgr = std::static_pointer_cast<ISessionManager>(GetManager<SessionManager>());
}


