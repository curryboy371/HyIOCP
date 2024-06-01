#pragma once


class ClientWin
{

public:
	ClientWin();
	~ClientWin();


public:
	void Init();
	void WorkThread(std::shared_ptr<IOCPClient> iocpRef);
public:

};

