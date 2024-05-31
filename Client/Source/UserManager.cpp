#include "pch.h"
#include "UserManager.h"

BEGIN_CLIENT

UserManager::UserManager()
    :myUser(nullptr)
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
}

END_CLIENT