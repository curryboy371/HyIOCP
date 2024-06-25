#include "pch.h"
#include "SpawnManager.h"

#include "Player.h"
#include "HyUtils.h"

std::atomic<int64> SpawnManager::SidGenerator = 1;

PlayerRef SpawnManager::CreatePlayer(const int64& Inuid)
{
	if (HyUtils::IsInvaildID(Inuid) == false)
	{
		ERR_V("InvalidID", Inuid);
		return nullptr;
	}

	const int64 newId = SidGenerator.fetch_add(1);

	PlayerRef player = std::make_shared<Player>();

	Protocol::hyps_object_info player_info;

	player_info.set_object_id(newId);
	player_info.set_object_type(Protocol::hype_object_type::creature);
	
	Protocol::hyps_pos_info* pos_info = new Protocol::hyps_pos_info();
	pos_info->set_x(HyUtils::GetRandom<float>(0, 100));
	pos_info->set_y(HyUtils::GetRandom<float>(0, 100));
	pos_info->set_z(0.f);
	pos_info->set_yaw(HyUtils::GetRandom<float>(0, 100));
	player_info.set_allocated_pos_info(pos_info);

	player->Set_player_info(player_info);
	player->Set_ownerUid(Inuid);

	return player;
}
