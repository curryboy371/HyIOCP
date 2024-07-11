#include "pch.h"
#include "UserManager.h"

#include "User.h"

#include "HyServerInstance.h"
#include "Room.h"

UserManager::UserManager()
{
    LOG_FUNC;
}

UserManager::~UserManager()
{
    LOG_FUNC;
}


void UserManager::InitManager()
{

}

void UserManager::ReleaseManager()
{
    for (auto& pair : userInfoMap)
    {
        pair.second->Get_ownerSession().reset();
    }

    userInfoMap.clear();
}

bool UserManager::AddUser(const Protocol::hyps_user_info& InuserInfo, HySessionRef userSession)
{
    if (InuserInfo.id() <= INVALID_UID)
    {
        return false;
    }

    if (Contains(userInfoMap, InuserInfo.id()) == false)
    {
        // user add
        UserRef user = std::make_shared<User>();
        user->Set_user_info(InuserInfo);
        user->Set_ownerSession(userSession);
        userInfoMap.emplace(InuserInfo.id(), user);
        return true;
    }

    return false;
}

bool UserManager::RemoveUse(HySessionRef userSession)
{
    int64 userID = userSession->GetSessionKey();
    if (userID <= INVALID_UID)
    {
        return false;
    }

    if (Contains(userInfoMap, userID) == true)
    {
        USE_MULOCK;

        // 룸 유저 정보 정리
        GSinstance->Get_room()->Leave(userInfoMap[userID]);

        userInfoMap[userID]->Get_ownerSession().reset();
        userInfoMap.erase(userID);
        return true;
    }

    return false;
}

bool UserManager::AddPlayerInfo(const int64& InUserID, const Protocol::hyps_object_info& InPlayerInfo)
{
    if (InUserID <= INVALID_UID)
    {
        return false;
    }

    if (Contains(userInfoMap, InUserID) == false)
    {
        return false;
    }

    if (userInfoMap[InUserID])
    {
        userInfoMap[InUserID]->Set_player_info(InPlayerInfo);
        userInfoMap[InUserID]->Set_bHasPlayerInfo(true);
        ++PlayerCount;
    }
    return true;
}

void UserManager::Broadcast(SendBufferRef sendBuffer)
{
    for (auto& pair : userInfoMap)
    {
        if (pair.second->Get_bHasPlayerInfo())
        {
            pair.second->Get_ownerSession()->PreSend(sendBuffer);
        }
    }
}

void UserManager::Broadcast(SendBufferRef sendBuffer, const int64& Inexcept_id)
{
    for (auto& pair : userInfoMap)
    {
        if (pair.first != Inexcept_id)
        {
            if (pair.second->Get_bHasPlayerInfo())
            {
                pair.second->Get_ownerSession()->PreSend(sendBuffer);
            }
        }
    }
}

UserRef UserManager::GetUser(const int64& userKey)
{
    if (Contains(userInfoMap, userKey) == true)
    {
        return userInfoMap[userKey];
    }

    return nullptr;
}
