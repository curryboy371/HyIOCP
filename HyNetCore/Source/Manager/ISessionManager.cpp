#include "Netpch.h"
#include "ISessionManager.h"

#include "HySession.h"

void ISessionManager::ReleaseSession()
{
	listenSession.reset();

	sessionID.store(0);

	for (auto& pair : connectedSessionMap)
	{
		pair.second->ClearSession();
	}

	connectedSessionMap.clear();
}


HySessionRef ISessionManager::GetUserSession(const int64& InuserId)
{
	if(Contains(connectedSessionMap, InuserId) == true)
	{ 
		return connectedSessionMap[InuserId];
	}

	// error
	return nullptr;
}

