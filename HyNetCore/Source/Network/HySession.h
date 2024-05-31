#pragma once

struct OverlappedEx;

struct PacketHeader
{
	uint16 size;
	uint16 id;
};

class HySession : public std::enable_shared_from_this<HySession>
{
	DEF_MUTEX

public:
	HySession() = delete;
	HySession(E_SESSION_TYPE inSessionType);
	virtual ~HySession();

public:
	// PreDoing > StartDoing > IO Event  > OnDoing > PostDoing

	// prefare func
	void PreDisconnect(const WCHAR* cause);
	void PreSend(SendBufferRef sendBufferRef);

	// start func
	bool StartConnect();
	bool StartDisconnect();
	bool StartSend();
	bool StartRecv();

	// event handler func
	void OnAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef);
	void OnConnect();
	void OnDisconnect();
	void OnRecv(OverlappedEx* overlappedEx);
	void OnSend(OverlappedEx* overlappedEx);

	// override func - call by event handler func ( OnDoing ) 
protected:
	virtual void PostAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef) abstract;
	virtual void PostConnect() abstract;
	virtual int32 PostRecv(BYTE* buffer, int32 len) abstract;
	virtual void PostSend(int32 len) abstract;

public:

public:
	void ClearSession();

public:
	// Invalid Check
	bool ValidIOType(E_IO_TYPE intype);

public:
	// Getter Setter
	SOCKET GetSocket() { return socket; }
	SOCKET& GetSocketRef() { return socket; }
	const E_SESSION_TYPE GetSessionType() { return sessionType; }
	bool IsConnected() { return (status == E_SESSION_STATUS::E_LOGIN_STATUS || status == E_SESSION_STATUS::E_CONNECT_STATUS); }
	bool IsLogined() { return status == E_SESSION_STATUS::E_LOGIN_STATUS; }

	const E_SESSION_STATUS GetSessionStatus() { return status; }
	void SetSessionStatus(const E_SESSION_STATUS newStatus) { status.store(newStatus); }

	void SetSessioKey(const int32 InKey) { sessionKey = InKey; }
	const int32 GetSessionKey() { return sessionKey; }

	void SetIOCPRef(std::shared_ptr<class IOCP> IniocpRef) { iocpRef = IniocpRef; }
	std::shared_ptr<class IOCP> GetIOCPRef() { return iocpRef; }

	void SetOverlappedOwner(E_IO_TYPE intype, std::shared_ptr<HySession> inOwnerSession);
	OverlappedEx& GetOverlappedRef(E_IO_TYPE intype);

	RecvBuffer& GetRecvBufferRef() { return recvBuffer; }

	HySessionRef GetSessionRef() { return std::static_pointer_cast<HySession>(shared_from_this()); }

protected:
	void CloseSocket();

protected:
	std::shared_ptr<class IOCP> iocpRef; // 부모 Iocp ref을 저장

protected:
	//send recv
	RecvBuffer recvBuffer;

	std::queue<SendBufferRef> sendBufferQueue;
	std::atomic<bool> bcanPushSendQ = false;

protected:
	SOCKET socket = INVALID_SOCKET;
	std::atomic<E_SESSION_STATUS> status;

	int32 sessionKey;

	E_SESSION_TYPE sessionType = E_SESSION_TYPE::E_SESSION_NONE;

	// 비동기 IO를 각 세션마다 각 타입 이벤트를 독립적으로 관리함
	OverlappedEx overlappedArr[static_cast<int>(E_IO_TYPE::E_IO_TYPE_MAX)];
};



