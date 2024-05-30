#pragma once

/*
	언리얼 gameinstance처럼
	하나의 인스턴스만 생성하여 전역적으로 관리
	manager 등
*/

#include "HyInstance.h"

extern HyClientInstanceRef Ginstance;

class HyClientInstance : public HyInstance
{
public:
	HyClientInstance();
	~HyClientInstance();

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

private:

};