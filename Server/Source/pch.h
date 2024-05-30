#pragma once

#include "Netpch.h"

#include "ServerSessions.h"
#include "ServerPacketHandler.h"

#include "HyServerInstance.h"

#include "UserManager.h"


#ifdef _DEBUG

#pragma comment(lib, "Libs\\HyNetCore\\Debug\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Debug\\libprotobufd.lib")

#else
#pragma comment(lib, "Libs\\HyNetCore\\Release\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Release\\libprotobuf.lib")

#endif
