#pragma once

#include "Protocol.pb.h"

class Player : public std::enable_shared_from_this<Player>
{
public:
	Player()
		:ownerUid(0)
	{};

	~Player() {};

public:
	const int64 GetPlayerID() { int64 object_id = player_info.object_id(); return object_id; }

public:
	GETTER(int64, ownerUid);
	SETTER(int64, ownerUid);

	GETTER(Protocol::hyps_object_info, player_info);
	SETTER(Protocol::hyps_object_info, player_info);

private:
	Protocol::hyps_object_info player_info;
	int64 ownerUid;
};

