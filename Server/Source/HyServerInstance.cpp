#include "pch.h"
#include "HyServerInstance.h"

#include "DBManager.h"
#include "UserManager.h"
#include "SessionManager.h"

#include "Room.h"

HyServerInstanceRef GSinstance;

HyServerInstance::HyServerInstance()
	:HyInstance(E_CORE_CONNECT::E_CONNECT_SERVER)
{
	LOG_FUNC;

}

HyServerInstance::~HyServerInstance()
{
	LOG_FUNC;
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

	Ginstance = shared_from_this();
	GSinstance = std::static_pointer_cast<HyServerInstance>(shared_from_this());;

	room = std::make_shared<Room>();
}

void HyServerInstance::ReleaseGInstance()
{
	HyInstance::ReleaseGInstance();

	Ginstance.reset();

	room->CleanRoom();// TODO temp
	room.reset();
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
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<TimeManager>()));
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<DBManager>()));


	for (auto& manager : managers)
	{
		manager->InitManager();
	}

	isessionMgr = std::static_pointer_cast<ISessionManager>(GetManager<SessionManager>());
}


