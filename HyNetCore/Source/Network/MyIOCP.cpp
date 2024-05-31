#include "Netpch.h"

#include "MyIOCP.h"

#include "HySession.h"
#include "Thread/LockGuard.h"

#include "ISessionManager.h"

#include "IOCPHandler.h"

IOCP::IOCP(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> Infunc, int32 InmaxSessionCount)
	:netAddr(InnetAddr), createSessionFunc(Infunc), maxSessionCount(InmaxSessionCount)
{

	// 윈소켓 초기화
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return;
	}

	// 런타임에 주소 얻어오는 api
	SOCKET dummySocket;
	CreateSocket(dummySocket);
	
	BindExFunction(dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx));
	BindExFunction(dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisconnectEx));
	BindExFunction(dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx));


	IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_SEND)] = [](HySessionRef& session, OverlappedEx* overlapped) { return IOCPHandler::OnSend(session, overlapped); };
	IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_RECV)] = [](HySessionRef& session, OverlappedEx* overlapped) { return IOCPHandler::OnReceive(session, overlapped); };
	IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_ACCEPT)] = [](HySessionRef& session, OverlappedEx* overlapped) { return IOCPHandler::OnAccept(session, overlapped); };
	IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_CONNECT)] = [](HySessionRef& session, OverlappedEx* overlapped) { return IOCPHandler::OnConnect(session, overlapped); };
	IOHandler[static_cast<int32>(E_IO_TYPE::E_IO_DISCONNECT)] = [](HySessionRef& session, OverlappedEx* overlapped) { return IOCPHandler::OnDisconnect(session,overlapped); };

	CreateCompletion();
}

IOCP::~IOCP()
{

	// 윈소켓 close
	::WSACleanup();

	std::cout << "~IOCP" << std::endl;
}

void IOCP::CreateCompletion()
{
	// Completion Port 생성
	iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}


std::shared_ptr<HySession> IOCP::CreateSession()
{
	std::shared_ptr<HySession> sessionRef = createSessionFunc();

	SetupSocket(sessionRef->GetSocketRef()); 
	return sessionRef;
}

void IOCP::SetupSocket(SOCKET& InSock)
{
	CreateSocket(InSock); // 세션 소켓 생성
	RegisterSocket(InSock); // 세션 소켓 completion port에 등록
}

bool IOCP::Bind(const SOCKET& inSocket, const NetAddress& inNetaddr)
{
	if (SOCKET_ERROR != ::bind(inSocket, reinterpret_cast<const SOCKADDR*>(&inNetaddr.GetSockAddr()), sizeof(inNetaddr.GetSockAddr())))
	{
		return true;
	}

	return false;
}

void IOCP::CreateSocket(SOCKET& OutSock)
{
	OutSock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	//OutSock = ::socket(AF_INET, SOCK_STREAM, 0);
	if (OutSock == INVALID_SOCKET || OutSock == UINT64_MAX)
	{
		int errCode = ::WSAGetLastError();

		return;
	}
}

void IOCP::RegisterSocket(const SOCKET& InSock)
{
	HANDLE socketHandle = reinterpret_cast<HANDLE>(InSock);
	::CreateIoCompletionPort(socketHandle, iocpHandle, /*key*/ 0, 0);
}

bool IOCP::BindExFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	DWORD bytes = 0;

	int Result = ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), OUT & bytes, NULL, NULL);
	return Result != SOCKET_ERROR;
}

void IOCP::ProcessIOCompletion(const DWORD& dwMilliSec /* = INFINITE*/)
{
	std::shared_ptr<HySession> sessionRef = nullptr;

	DWORD bytesTransferred = 0; // 완료 IO 작업 bytes
	ULONG_PTR completionKey = 0; // 완료 key - 미사용, overlapped 구조체를 활용함
	LPOVERLAPPED overlapped = nullptr; //완료 IO와 연관된 OVERLAPPED 구조체 주소
	//DWORD dwMilliSec = INFINITE; // 완료 포트에서 IO 작업을 기다리는 시간, 0이면 즉시 반환, INFINITE 는 무한대기

	bool ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, &completionKey, &overlapped, dwMilliSec);

	OverlappedEx* overlappedEx = reinterpret_cast<OverlappedEx*>(overlapped);

	if (ret == false)
	{
		int errCode = ::WSAGetLastError();
		if (nullptr != overlapped || WAIT_TIMEOUT != errCode) // timeout이 아님
		{
			sessionRef = overlappedEx->GetOwnerSessionRef();
			std::wstring errStr = WSALOG(errCode);
			sessionRef->PreDisconnect(LOG_INFO(errStr));
		}

		return;
	}

	// Overlapped 에 IO 정보가 정상적으로 들어온 상황
	sessionRef = overlappedEx->GetOwnerSessionRef();
	overlappedEx->SetBytes(bytesTransferred); // byteSet

	// IOCP Event 실행
	ProcessIOEvent(overlappedEx);
}

void IOCP::ProcessIOEvent(OverlappedEx* overlappedEx)
{
	std::shared_ptr<HySession> sessionRef = overlappedEx->GetOwnerSessionRef();
	overlappedEx->ResetOwner();

	E_IO_TYPE type = overlappedEx->GetIOType();

	IOHandler[static_cast<int32>(type)](sessionRef, overlappedEx);
}

void IOCP::Send(HySessionRef sessionRef, SendBufferRef sendBufferRef)
{
	sessionRef->PreSend(sendBufferRef);
}

void IOCP::SendBroadcast(SendBufferRef sendBufferRef)
{
	//for (auto& pair : conSessionMap)
	//{
	//	if (pair.second->IsLogined())
	//	{
	//		pair.second->PreSend(sendBufferRef);
	//	}
	//}
}

IOCPServer::IOCPServer(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> InListenSFunc, std::function<std::shared_ptr<HySession>(void)> InClientSFunc, int32 InmaxSessionCount)
	:IOCP(InnetAddr, InClientSFunc, InmaxSessionCount), createListenSessionFunc(InListenSFunc)
{
}

IOCPServer::~IOCPServer()
{

	listenSessionRef->ClearSession();

	std::cout << "~IOCPServer" << std::endl;

}

bool IOCPServer::InitIOCP()
{
	// 여기서는 listen server session 생성해줌.
	listenSessionRef = CreateListenSession();
	GisessionMgr->Set_listenSession(listenSessionRef);
	
	// TODO?
	if (false == SetSockOpt(listenSessionRef->GetSocketRef(), SOL_SOCKET, SO_REUSEADDR, true))
	{
		return false;
	}

	// TODO?
	LINGER option;
	option.l_onoff = 0;
	option.l_linger = 0;
	if (false == SetSockOpt(listenSessionRef->GetSocketRef(), SOL_SOCKET, SO_LINGER, option))
	{
		return false;
	}

	if (false == Bind(listenSessionRef->GetSocketRef(), netAddr))
	{
		// bind error
		return false;
	}

	if (false == Listen())
	{
		// listen error
		return false;
	}

	if (false == MakeClientSession())
	{
		// make client session error
		return false;
	}

	return true;
}

bool IOCPServer::MakeClientSession()
{
	// 이것을 블라킹 방식이 아닌..
	// callback 함수로 받는 식의 non block으로...
	// session은 미리 만들어두고.. 연결하는 식을 사용하겟음.

	for (int i = 0; i < maxSessionCount; ++i)
	{
		// 이부분은 메인 스레드가 최초 실행시에만 담당하므로 lock을 걸지 않음.
		std::shared_ptr<HySession> clientSessionRef = CreateSession();
		Accept(clientSessionRef);
	}

	return true;
}

std::shared_ptr<HySession> IOCPServer::CreateListenSession()
{
	//std::shared_ptr<HySession> sessionRef = std::make_shared<ListenSession>(E_SESSION_TYPE::E_SESSION_LISTEN);
	std::shared_ptr<HySession> sessionRef = createListenSessionFunc();

	SetupSocket(sessionRef->GetSocketRef());
	
	return sessionRef;
}

bool IOCPServer::Listen()
{
	return SOCKET_ERROR != ::listen(listenSessionRef->GetSocketRef(), SOMAXCONN);
}

bool IOCPServer::PreAccept(std::shared_ptr<HySession> sessionRef, const bool bRetry/* = false*/)
{
	// ref 설정
	sessionRef->SetIOCPRef(shared_from_this());

	return GisessionMgr->OnAddConnectedSession(sessionRef, bRetry);
}

void IOCPServer::Accept(std::shared_ptr<HySession> sessionRef, const bool bRetry/* = false*/)
{
	// 세션을 미리 만들어두고 클라이언트 연결을 기다리는 구조임
	// 연결여부는 status 변수로 구분함.

	// Accpet 등록 이전에 생성한 client session에서 처리할 것을 해둠
	bool bret = PreAccept(sessionRef, bRetry);

	if (bret)
	{
		DWORD byteReceived = 0;
		if (false == Get_AcceptEx()(listenSessionRef->GetSocketRef(), sessionRef->GetSocket(), sessionRef->GetRecvBufferRef().WritePos(), 0,
			sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
			OUT & byteReceived, static_cast<LPOVERLAPPED>(&(sessionRef->GetOverlappedRef(E_IO_TYPE::E_IO_ACCEPT)))))
		{
			const int errCode = ::WSAGetLastError();
			if (errCode != WSA_IO_PENDING)
			{
				// 다시 Accept 시도
				Accept(sessionRef);
			}
		}
	}
	else 
	{
		std::cout << "Accept Error" << std::endl;
	}


}

IOCPClient::IOCPClient(NetAddress InnetAddr, std::function<std::shared_ptr<HySession>(void)> InFunc, int32 InmaxSessionCount)
	:IOCP(InnetAddr, InFunc, InmaxSessionCount)
{
}

IOCPClient::~IOCPClient()
{

	std::cout << "~IOCPClient" << std::endl;
}

bool IOCPClient::InitIOCP()
{
	// 클라-서버 세션 생성
	for (int i = 0; i < maxSessionCount; ++i)
	{
		// 세션을 먼저 생성하고 서버에 connect 요청을 함
		HySessionRef sessionRef = CreateSession();
		sessionRef->SetIOCPRef(shared_from_this());

		bool bSuccess = sessionRef->StartConnect();

		if (false == bSuccess)
		{
			//error
			return false;
		}
	}
	return true;
}

