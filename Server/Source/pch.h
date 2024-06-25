#pragma once

#include "Netpch.h"

#include "HyUtils.h"

#include "ServerSessions.h"
#include "ServerPacketHandler.h"

#include "HyServerInstance.h"

#include "UserManager.h"

#include "Protocol.pb.h"

// db
#include <mysql/jdbc.h>


#ifdef _DEBUG
#pragma comment(lib, "Libs\\mysqlcppcon\\Debug\\mysqlcppconn.lib")
#pragma comment(lib, "Libs\\HyNetCore\\Debug\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Debug\\libprotobufd.lib")

#else
#pragma comment(lib, "Libs\\HyNetCore\\Release\\HyNetCore.lib")
#pragma comment(lib, "Libs\\Protobuf\\Release\\libprotobuf.lib")

#endif
