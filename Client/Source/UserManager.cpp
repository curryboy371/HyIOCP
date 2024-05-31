#include "pch.h"
#include "UserManager.h"

BEGIN_CLIENT

UserManager::UserManager()
    :myUser(nullptr)
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
}

END_CLIENT