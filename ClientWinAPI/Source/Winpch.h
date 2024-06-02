#pragma once
#include "Netpch.h"
#include "pch.h" // client lib

#include "ClientSessions.h"
#include "ClientPacketHandler.h"

#include "HyClientInstance.h"

#include "framework.h"
#include "ClientWinAPI.h"
#include <iostream>
#include <string>

#ifdef _DEBUG
#pragma comment(lib, "Libs\\Client\\Debug\\Client.lib")
#pragma comment(lib, "Libs\\HyNetCore\\Debug\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Debug\\libprotobufd.lib")

#else
#pragma comment(lib, "Libs\\HyNetCore\\Release\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Release\\libprotobuf.lib")
#endif
