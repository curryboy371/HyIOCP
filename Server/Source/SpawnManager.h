#pragma once

#include "BaseManager.h"

class SpawnManager : public BaseManager
{
public:
	static PlayerRef CreatePlayer(const int64& Inuid);

private:
	static std::atomic<int64> SidGenerator;
};

