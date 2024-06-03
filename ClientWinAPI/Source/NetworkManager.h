#pragma once


#include "BaseManager.h"
class NetworkManager : public BaseManager
{
public:
	NetworkManager();
	~NetworkManager();

public:
	// BaseManager을(를) 통해 상속됨
	virtual void InitManager() override;
	virtual void ReleaseManager() override;


	void CallnetworkCB(HyPacketID packetID);

	void Send_CS_LOGIN(std::string use_id, std::string use_pw, std::function<void()> cb);

private:
	SETTER(HySessionRef, sessionRef);
private:
	HySessionRef sessionRef;

private:
	std::unordered_map<HyPacketID, std::function<void()>> networkCallBackMap;
};

