#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "Header/HyType.h"
class NetAddress
{
public:

	NetAddress() = delete;

	NetAddress(SOCKADDR_IN InsockAddr)
		:sockAddr(InsockAddr)
	{

	}

	NetAddress(std::wstring ip, unsigned short port)
	{
		::memset(&sockAddr, 0, sizeof(sockAddr));

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr = Ip2Address(ip.c_str());
		sockAddr.sin_port = ::htons(port);

	}


	const SOCKADDR_IN& GetSockAddr() const { return sockAddr; }

	std::wstring GetIpAddress() const
	{
		WCHAR buffer[100];

		int32 size = static_cast<int32>(sizeof(buffer) / sizeof(WCHAR));
		::InetNtopW(AF_INET, &sockAddr.sin_addr, buffer, size);
		return std::wstring(buffer);
	}

	const unsigned short GetPort() const { return ::ntohs(sockAddr.sin_port); }

	static IN_ADDR Ip2Address(const WCHAR* ipAddr)
	{
		IN_ADDR address;
		::InetPtonW(AF_INET, ipAddr, &address);
		return address;
	}

private:
	SOCKADDR_IN sockAddr = {};
};