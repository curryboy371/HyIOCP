#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::InitManager()
{
}

void NetworkManager::ReleaseManager()
{
	sessionRef.reset();
}

void NetworkManager::CallnetworkCB(HyPacketID packetID)
{
	networkCallBackMap[packetID]();
}

void NetworkManager::Send_CS_LOGIN(std::string use_id, std::string use_pw, std::function<void()> cb)
{
	Protocol::CS_LOGIN loginPkt;
	std::string userName = use_id;
	loginPkt.set_user_name(userName);
	loginPkt.set_passwd(use_pw);
	loginPkt.set_bisdevlogin(GCinstance->Get_bIsDevMode());

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	GCinstance->Get_IocpRef()->Send(sessionRef, sendBuffer);

	if (GCinstance->Get_bIsDevMode() == false)
	{
		networkCallBackMap.emplace(HyPacketID::PKE_SC_LOGIN, cb);
	}
	else
	{
		networkCallBackMap.emplace(HyPacketID::PKE_SC_LOGIN, []() {});
	}
}
