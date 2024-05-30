#pragma once


class BaseManager : public std::enable_shared_from_this<BaseManager>
{
public:
	BaseManager();
	virtual ~BaseManager();

public:
	virtual void InitManager() abstract;
	virtual void ReleaseManager() abstract;

};

