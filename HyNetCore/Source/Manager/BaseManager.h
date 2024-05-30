#pragma once


class BaseManager
{
public:
	BaseManager();
	virtual ~BaseManager();

public:
	virtual void InitManager() abstract;
	virtual void ReleaseManager() abstract;

};

