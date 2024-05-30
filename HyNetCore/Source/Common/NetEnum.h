#pragma once


enum class E_IO_TYPE : unsigned char
{
	E_IO_SEND,
	E_IO_RECV,
	E_IO_ACCEPT,
	E_IO_CONNECT,
	E_IO_DISCONNECT,
	E_IO_TYPE_MAX
};

#pragma region Session

enum class E_SESSION_TYPE : unsigned char
{
	E_SESSION_NONE,
	E_SESSION_LISTEN,	// 서버 리슨세션			- in Server
	E_SESSION_S2C,		// 서버에서 연결한 클라세션 - in Server
	E_SESSION_C2S,		// 클라에서 연결한 서버세션 - in Client
	E_SESSION_C2C,		// 
	E_SESSION_S2S,		// 

};

enum class E_SESSION_STATUS : unsigned char
{
	E_NONE_STATUS,			// 최초 디폴트 상태
	E_WAIT_STATUS,			// 연결 대기상태  accept, connect 
	E_CONNECT_STATUS,		// 연결 상태
	E_LOGIN_STATUS,			// 로그인 완료 상태 // client session만
	E_DISCONNECT_STATUS,	// 연결 끊어진 상태
	E_RETRY_STATUS,			// 연결 재시도 상태
};

#pragma endregion 
