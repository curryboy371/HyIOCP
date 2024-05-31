#include "pch.h"
#include "HyClientInstance.h"

#include "UserManager.h"
#include "SessionManager.h"

HyClientInstanceRef GCinstance;

HyClientInstance::HyClientInstance()
	:HyInstance(E_CORE_CONNECT::E_CONNECT_CLIENT)
{
	LOG_FUNC;

}

HyClientInstance::~HyClientInstance()
{
	LOG_FUNC;
}

void HyClientInstance::InitHyInstance()
{
	InitGInstance();
	InitProtocol();
	InitManager();
}

void HyClientInstance::ReleaseInstance()
{
	ReleaseGInstance();
	ReleaseManager();
}

void HyClientInstance::InitGInstance()
{
	HyInstance::InitGInstance();

	Ginstance = shared_from_this();
	GCinstance = std::static_pointer_cast<HyClientInstance>(shared_from_this());
}

void HyClientInstance::ReleaseGInstance()
{
	HyInstance::ReleaseGInstance();

	GCinstance.reset();


}

void HyClientInstance::ReleaseManager()
{
	HyInstance::ReleaseManager();

}

void HyClientInstance::InitProtocol()
{
	ClientPacketHandler::Init();
}

void HyClientInstance::InitManager()
{
	// 언리얼처럼 Reflection 기능이 있다면 하나하나 만들진 않아도 되는데..
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<Client::UserManager>()));
	managers.push_back(std::static_pointer_cast<BaseManager>(std::make_shared<Client::SessionManager>()));

	for (auto& manager : managers)
	{
		manager->InitManager();
	}

	isessionMgr = std::static_pointer_cast<ISessionManager>(GetManager<Client::SessionManager>());
}


