#pragma once


/*
	언리얼 gameinstance처럼
	하나의 인스턴스만 생성하여 전역적으로 관리
	manager 등
*/

class UserManager;
class NetGlobal;
//class Room;

class HyClientInstance
{
public:
	HyClientInstance();
	~HyClientInstance();

public:
	void InitInstance();
	void ReleaseInstance();

protected:
	void InitProtocol();
	void InitManager();
	void ReleaseManager();

public:
	static UserManagerRef GetUserMgr() { return userMgr; };
	//static RoomRef GetRoom() { return room; };

private:
	static UserManagerRef userMgr;

	//static RoomRef room;

	NetGlobalRef netG;

};

