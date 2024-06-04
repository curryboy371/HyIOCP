#include "pch.h"
#include "UserManager.h"
#include "User.h"

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

    for (auto& user : myUsers)
    {
        user->Get_ownerSession().reset();
    }

    myUsers.clear();


    userInfoMap.clear();
}

bool UserManager::AddClientSession(UserRef user)
{
    myUsers.push_back(user);
    return false;
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
        //GCinstance->Get_room()->Leave(userInfoMap[userID]);

        userInfoMap[userID]->Get_ownerSession().reset();
        userInfoMap.erase(userID);
        return true;
    }

    return false;
}

UserRef UserManager::GetUser(const int64& userKey)
{
    if (Contains(userInfoMap, userKey) == true)
    {
        return userInfoMap[userKey];
    }

    return nullptr;
}

UserRef UserManager::GetMyUser(const int64& userKey/* = 0*/)
{
    return myUsers[userKey];
}

bool UserManager::GetMyUsers(std::vector<UserRef>& OutUsers)
{
    if (myUsers.size() > 0)
    {
        OutUsers = myUsers;
        return true;
    }
    return false;
}


