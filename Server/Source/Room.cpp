#include "pch.h"
#include "Room.h"
#include "User.h"

void Room::CleanRoom()
{
	users.clear();

}

void Room::Enter(UserRef user)
{
	users[user->GetUserID()] = user;

}

void Room::Leave(UserRef user)
{
	users.erase(user->GetUserID());
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	for (auto& user : users)
	{
		user.second->Get_ownerSession()->PreSend(sendBuffer);
	}
}

void Room::Broadcast(SendBufferRef sendBuffer, const int64& except_id)
{
	for (auto& user : users)
	{
		if (except_id == user.second->GetUserID())
		{
			continue;
		}

		user.second->Get_ownerSession()->PreSend(sendBuffer);
	}
}


void Room::SetUserList(std::vector<UserRef>& Outusers)
{
	Outusers.reserve(static_cast<int32>(users.size()));
	for (auto& user : users)
	{
		Outusers.push_back(user.second);
	}
}

void Room::FlushJob()
{
	while (true)
	{
		JobRef job = jobs.Pop();
		if (job == nullptr)
		{
			break;
		}

		job->Excute();
	}
}
