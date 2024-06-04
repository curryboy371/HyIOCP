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


	void CallnetworkCB(HyPacketID packetID, int32 result);

	void Send_CS_LOGIN(HySessionRef sessionRef, std::string use_id, std::string use_pw, std::function<void(int32)> cb);
	void Send_CS_REGIST(HySessionRef sessionRef, std::string use_id, std::string use_pw, std::function<void(int32)> cb);

private:
	GETTER(HySessionRef, mySession);
	SETTER(HySessionRef, mySession);
private:
	HySessionRef mySession;

private:
	std::unordered_map<HyPacketID, std::function<void(int32)>> networkCallBackMap;
};

