#include "pch.h"
#include "Room.h"
#include "User.h"

#include "UserManager.h"
#include "HyClientInstance.h"

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
	std::vector<UserRef> Myusers;
	GCinstance->GetManager<UserManager>()->GetMyUsers(Myusers);

	for (auto& myuser : Myusers)
	{
		DLOG_V("broacast", myuser->Get_user_infoRef().name());
		if (myuser->Get_ownerSession())
		{
			DoAsync([myuser, sendBuffer]() {myuser->Get_ownerSession()->PreSend(sendBuffer); });
		}
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
