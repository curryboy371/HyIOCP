#include "Netpch.h"
#include "HySession.h"

#include "ISessionManager.h"

HySession::HySession(E_SESSION_TYPE inSessionType)
	:sessionType(inSessionType), status(E_SESSION_STATUS::E_NONE_STATUS), bcanPushSendQ(false),
	recvBuffer(RECV_BURRER_SIZE), socketName("")
{
	// 소켓 초기화
	socket = INVALID_SOCKET;

	// Overlapped 배열 초기화
	for (int i = 0; i < static_cast<int>(E_IO_TYPE::E_IO_TYPE_MAX); ++i)
	{
		overlappedArr[i].Init();
		overlappedArr[i].SetIOType(static_cast<E_IO_TYPE>(i));
	}
}

HySession::~HySession()
{
	ClearSession();

	LOG_FUNC;
}

void HySession::ClearSession()
{
	SetSessionStatus(E_SESSION_STATUS::E_DISCONNECT_STATUS);

	// overlapped 구조체 초기화
	for (int i = 0; i < static_cast<int>(E_IO_TYPE::E_IO_TYPE_MAX); ++i)
	{
		overlappedArr[i].Init();
	}

	// close Socket
	CloseSocket();
}

void HySession::CloseSocket()
{
	if (socket != INVALID_SOCKET)
	{
		::closesocket(socket);
	}

	socket = INVALID_SOCKET;
}

void HySession::OnAccept(OverlappedEx* overlappedEx, std::shared_ptr<HySession> sessionRef)
{
	OnPostAccept(overlappedEx, sessionRef);
}

void HySession::OnConnect()
{
	LOG_FUNC;
	OnPostConnect();

}

void HySession::OnDisconnect()
{
	LOG_FUNC;
	OnPostDisconnect();
}

void HySession::OnRecv(OverlappedEx* overlappedEx)
{
	//std::shared_ptr<HySession> sessionRef = overlappedEx->GetOwnerSessionRef();
	DWORD byteSize = overlappedEx->GetByteSize();

	if (0 == byteSize)
	{
		PreDisconnect(LOG_INFO(L"byteSize size zero"));
		return;
	}

	if (false == recvBuffer.OnWrite(byteSize))
	{
		PreDisconnect(LOG_INFO(L"OnWrite fail"));
		return;
	}

	int32 dataSize = recvBuffer.DataSize();

	int32 headerSize = sizeof(FPacketHeader);
	int32 processLen = 0;

	BYTE* readByte = recvBuffer.ReadPos();

	// 여러 패킷을 한번에 받을 수 있으므로 처리함
	while (true)
	{
		int32 remainSize = dataSize - processLen;
		if (remainSize < headerSize) // header 파싱 여부
		{
			break;
		}

		FPacketHeader header = *reinterpret_cast<FPacketHeader*>(&readByte[processLen]);

		int32 packetSize = header.PacketSize;
		int32 packetID = header.PacketID;
		if (remainSize < packetSize) // data 파싱 여부
		{
			break;
		}

		int32 resLen = OnPostRecv(&readByte[processLen], packetSize);
		processLen += resLen;
	}

	if (processLen < 0 || dataSize < processLen || recvBuffer.OnRead(processLen) == false)
	{
		PreDisconnect(LOG_INFO(L"processLen fail"));
		return;
	}

	recvBuffer.Clean();
}

void HySession::OnSend(OverlappedEx* overlappedEx)
{
	if (false == IsConnected())
	{
		return;
	}

	//DLOG_V("OnSend ByteSize", overlappedEx->GetByteSize());

	{
		USE_MULOCK;
		if (sendBufferQueue.empty())
		{
			bcanPushSendQ.store(false);
		}
		else
		{
			//잔여 버퍼 Send
			StartSend();
		}
	}
	
}

void HySession::PreDisconnect(const WCHAR* cause)
{
	// 1. PreDisconnect 
	// 이상 데이터 감지시 PreDisconnect를 호출하여 StartDisconnect 실행

	auto checkAndSetStatus = [&](E_SESSION_STATUS expectedStatus) 
	{
		return status.compare_exchange_strong(expectedStatus, E_SESSION_STATUS::E_DISCONNECT_STATUS);
	};

	if (checkAndSetStatus(E_SESSION_STATUS::E_LOGIN_STATUS) || checkAndSetStatus(E_SESSION_STATUS::E_CONNECT_STATUS)) {
		std::wcout << "PreDisconnect : " << cause << std::endl;
		StartDisconnect();
	}
	else {
		std::wcout << "PreDisconnect Duplicate : " << cause << std::endl;
		return;
	}
}

bool HySession::StartConnect()
{
	if (IsConnected() == true)
	{
		return false;
	}

	IOCP::SetSockOpt(GetSocketRef(), SOL_SOCKET, SO_REUSEADDR, true);

	// bind
	SOCKADDR_IN address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = ::htonl(INADDR_ANY);
	address.sin_port = ::htons(0); // any port

	IOCPRef iocpRef = Ginstance->Get_IocpRef();

	if (!iocpRef)
	{
		return false;
	}

	if (false == iocpRef->Bind(GetSocketRef(), address))
	{
		// bind error
		return false;
	}

	SetOverlappedOwner(E_IO_TYPE::E_IO_CONNECT, shared_from_this());
	DWORD numOfBytes;

	SOCKADDR_IN sockAddr = iocpRef->GetNetAddress().GetSockAddr();

	if (false == iocpRef->Get_ConnectEx()(GetSocketRef(), reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, &GetOverlappedRef(E_IO_TYPE::E_IO_CONNECT)))
	{
		int32 errCode = ::WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			GetOverlappedRef(E_IO_TYPE::E_IO_CONNECT).ResetOwner();
			return false;
		}
	}

	SetSessionStatus(E_SESSION_STATUS::E_WAIT_STATUS);
	return true;

}

void HySession::PreSend(SendBufferRef sendBufferRef)
{
	if (false == IsConnected())
	{
		return;
	}

	bool bstartSend = false;

	// 보낼 데이터를 sendEvent에 등록
	// PreSend에서 SendQueue Push와 StartSend 등록함수의 Lock 경합을 따로 처리하려고 bcanPushSendQ atomic bool이 중간에 꼈음.
	{
		USE_MULOCK;
		sendBufferQueue.push(sendBufferRef);

		if (bcanPushSendQ.exchange(true) == false)
		{
			bstartSend = true;
		}
	}

	// sendqueue push와 StartSend
	if (bstartSend)
	{
		StartSend();
	}

}

bool HySession::StartDisconnect()
{
	// 2. StartDisconnect 
	// Component Port로 현 세션의 Disconnect event를 등록한다

	SetOverlappedOwner(E_IO_TYPE::E_IO_DISCONNECT, shared_from_this());

	if (false == Ginstance->Get_IocpRef()->Get_DisconnectEx()(GetSocketRef(), &GetOverlappedRef(E_IO_TYPE::E_IO_DISCONNECT), TF_REUSE_SOCKET, 0))
	{
		int32 errCode = ::WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			GetOverlappedRef(E_IO_TYPE::E_IO_DISCONNECT).ResetOwner();
			return false;
		}
	}

	return true;
}

bool HySession::StartSend()
{
	if (IsConnected() == false)
	{
		return false;
	}

	// SendBuferQueue > wsaBufs로 변경하여 채워넣음.
	{
		USE_MULOCK;

		SetOverlappedOwner(E_IO_TYPE::E_IO_SEND, shared_from_this());

		// Scatter-Gather ( 데이터를 모아 한방에 보냄 )
		std::vector<WSABUF> wsaBufs;
		wsaBufs.reserve(sendBufferQueue.size());

		int32 writeSize = 0;

		while (false == sendBufferQueue.empty())
		{
			SendBufferRef sendBufferR = sendBufferQueue.front();
			writeSize += sendBufferR->WriteSize();

			if (MAX_RECV_SIZE <= writeSize)
			{
				break;
			}

			WSABUF wsaBuf;
			wsaBuf.buf = reinterpret_cast<char*>(sendBufferR->Buffer());
			wsaBuf.len = static_cast<LONG>(sendBufferR->WriteSize());
			wsaBufs.push_back(wsaBuf);
			sendBufferQueue.pop();
		}

		// 채워넣은 wsaBuffers를 Send
		DWORD numOfByte = 0;
		if (SOCKET_ERROR == ::WSASend(GetSocketRef(), wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT & numOfByte, 0, &(GetOverlappedRef(E_IO_TYPE::E_IO_SEND)), nullptr))
		{
			int errCode = ::WSAGetLastError();
			if (errCode != WSA_IO_PENDING)
			{
				GetOverlappedRef(E_IO_TYPE::E_IO_SEND).ResetOwner();
				bcanPushSendQ.store(false);
				return false;
			}
		}
	}

	return true;
}

bool HySession::StartRecv()
{
	if (false == IsConnected())
	{
		return false;
	}

	SetOverlappedOwner(E_IO_TYPE::E_IO_RECV, shared_from_this());

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(GetRecvBufferRef().WritePos());
	wsaBuf.len = GetRecvBufferRef().FreeSize();

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	if (SOCKET_ERROR == ::WSARecv(GetSocketRef(), &wsaBuf, 1, OUT & numOfBytes, OUT & flags, &(GetOverlappedRef(E_IO_TYPE::E_IO_RECV)), nullptr))
	{
		int errCode = ::WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			ERR_V("WSARecv %d", errCode);
			GetOverlappedRef(E_IO_TYPE::E_IO_RECV).ResetOwner();
			return false;
		}
	}

	return true;
}

void HySession::SetOverlappedOwner(E_IO_TYPE intype, std::shared_ptr<HySession> inOwnerSession)
{
	GetOverlappedRef(intype).Init();
	GetOverlappedRef(intype).SetOwnerSessionRef(inOwnerSession);
}


OverlappedEx& HySession::GetOverlappedRef(E_IO_TYPE intype)
{
	if (ValidIOType(intype))
	{
		return overlappedArr[static_cast<int>(intype)];
	}
	else
	{
		// error
		ERR_V("GetOverlappedRef Invalid E_IO_TYPE value %d", static_cast<int32>(intype));
		static OverlappedEx defOverlapped;
		return defOverlapped;
	}
}

bool HySession::ValidIOType(E_IO_TYPE intype)
{
	return (intype < E_IO_TYPE::E_IO_TYPE_MAX && intype >= E_IO_TYPE::E_IO_SEND);
}

