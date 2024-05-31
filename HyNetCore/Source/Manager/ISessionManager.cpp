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
