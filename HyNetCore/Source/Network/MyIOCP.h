#pragma once


class HySession;

// SessionConfig 
template<typename T>
class SessionConfig 
{
public:
	// 생성자 추가
	SessionConfig() = delete;
	SessionConfig(const std::wstring& ip, uint16_t port, E_SESSION_TYPE type, int32 InmaxSessionCount)
		:address{ ip, port }, sessionType(type), maxSessionCount(InmaxSessionCount)
	{
		sessoinfactory = [=]() { return std::make_shared<T>(GetSessionType()); };
	}

	std::shared_ptr<T> CreateSession() const { return sessoinfactory();}
	NetAddress& GetAddress() { return address; }

	std::function<std::shared_ptr<T>(void)> GetSessionFactory() { return sessoinfactory; }

	E_SESSION_TYPE GetSessionType() { return sessionType; }
	int32 GetMaxSessionCount() const { return maxSessionCount; }
	
private:
	NetAddress address;
	std::function<std::shared_ptr<T>(void)> sessoinfactory;

	E_SESSION_TYPE sessionType;

	int32 maxSessionCount;
};

using IOCPHandlerFunc = std::function<bool(HySessionRef&, OverlappedEx*)>;

class IOCP : public std::enable_shared_from_this<IOCP>
{
	DEF_MUTEX
public:
	IOCP(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> InFunc, int32 InmaxSessionCount);
	virtual ~IOCP();

public:
	virtual bool InitIOCP() abstract;

	std::shared_ptr<HySession> CreateSession();
	virtual void Accept(std::shared_ptr<HySession> sessionRef, const bool bRetry = false) {};

	virtual bool Bind(const SOCKET& inSocket, const NetAddress& inNetaddr);

	void SetupSocket(SOCKET& InSock);

public:
	void ProcessIOCompletion(const DWORD& dwMilliSec = INFINITE);
	void ProcessIOEvent(OverlappedEx* overlappedEx);

public:
	void Send(HySessionRef sessionRef, SendBufferRef sendBufferRef);
	void SendBroadcast(SendBufferRef sendBufferRef);

protected:
	void CreateCompletion();

	void CreateSocket(SOCKET& OutSock);
	void RegisterSocket(const SOCKET& InSock);

	bool BindExFunction(SOCKET socket, GUID guid, LPVOID* fn);

public:
	template<typename T>
	static inline bool SetSockOpt(SOCKET socket, int level, int optName, T optVal)
	{
		return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
	}


public:
	GETTER(LPFN_CONNECTEX, ConnectEx);
	GETTER(LPFN_DISCONNECTEX, DisconnectEx);
	GETTER(LPFN_ACCEPTEX, AcceptEx);

public:

	NetAddress& GetNetAddress() { return netAddr; }
protected:
	NetAddress netAddr;
	std::function<std::shared_ptr<HySession>(void)> createSessionFunc;
	int32 maxSessionCount;
	HANDLE iocpHandle;
	SOCKET sock; // main socket


	LPFN_CONNECTEX		ConnectEx;
	LPFN_DISCONNECTEX	DisconnectEx;
	LPFN_ACCEPTEX		AcceptEx;

	IOCPHandlerFunc IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_TYPE_MAX)];
};


class IOCPClient : public IOCP
{
public:
	IOCPClient(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> InFunc, int32 InmaxSessionCount);
	virtual ~IOCPClient();

public:
	virtual bool InitIOCP() override;

public:


protected:


};


class IOCPServer : public IOCP
{
public:
	IOCPServer(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> InListenSFunc, std::function<std::shared_ptr<HySession>(void)> InClientSFunc, int32 InmaxSessionCount);
	virtual ~IOCPServer();

public:
	virtual bool InitIOCP() override;

	bool PreAccept(std::shared_ptr<HySession> sessionRef, const bool bRetry = false);
	void Accept(std::shared_ptr<HySession> sessionRef, const bool bRetry = false);

public:

protected:
	bool Listen();

	std::shared_ptr<HySession> CreateListenSession();

	bool MakeClientSession();

protected:
	std::function<std::shared_ptr<HySession>(void)> createListenSessionFunc;
	std::shared_ptr<HySession> listenSessionRef = nullptr; // listen session

};

