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
}

void NetworkManager::CallnetworkCB(HyPacketID packetID, int32 result)
{
	networkCallBackMap[packetID](result);
}

void NetworkManager::Send_CS_LOGIN(HySessionRef sessionRef, std::string use_id, std::string use_pw, std::function<void(int32)> cb)
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
		networkCallBackMap.emplace(HyPacketID::PKE_SC_LOGIN, [](int32 result) {});
	}
}

void NetworkManager::Send_CS_REGIST(HySessionRef sessionRef, std::string use_id, std::string use_pw, std::function<void(int32)> cb)
{
	Protocol::CS_REGIST registPkt;
	std::string userName = use_id;
	registPkt.set_user_name(userName);
	registPkt.set_passwd(use_pw);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(registPkt);
	GCinstance->Get_IocpRef()->Send(sessionRef, sendBuffer);

	networkCallBackMap.emplace(HyPacketID::PKE_SC_REGIST, cb);
}
