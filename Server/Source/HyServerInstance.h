#pragma once

/*

	언리얼 gameinstance처럼
	하나의 인스턴스만 생성하여 전역적으로 관리
	manager 등

*/

#include "HyInstance.h"

extern HyServerInstanceRef GSinstance;

extern RoomRef Groom;

class HyServerInstance : public HyInstance
{
public:
	HyServerInstance();
	~HyServerInstance();

public:
	virtual void InitHyInstance();
	virtual void ReleaseInstance();

protected:
	virtual void InitGInstance();

	virtual void InitProtocol();
	virtual void InitManager();

	virtual void ReleaseGInstance();
	virtual void ReleaseManager();

public:
	RoomRef GetRoom() { return Groom; };



};

