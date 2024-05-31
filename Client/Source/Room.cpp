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
