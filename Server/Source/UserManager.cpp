#include "pch.h"
#include "UserManager.h"

#include "User.h"

UserManager::UserManager()
{
    DEF_LOG;
}

UserManager::~UserManager()
{
    DEF_LOG;
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

UserRef UserManager::GetUser(const int64& userKey)
{
    if (Contains(userInfoMap, userKey) == true)
    {
        return userInfoMap[userKey];
    }

    return nullptr;
}
