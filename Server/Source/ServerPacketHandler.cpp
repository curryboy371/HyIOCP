#pragma once
#include "pch.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"

#include "Room.h"
#include "User.h"

#include "SessionManager.h"
#include "DBManager.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

/* 서버 side 패킷 수신 */

/* 컨텐츠 수동 작업 */
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len)
{
    FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
    std::cout << "\nINVALID_PACKET:: id " << header->PacketID << std::endl;
    return false;
}


bool CS_LOGIN(HySessionRef& session, Protocol::CS_LOGIN& pkt)
{
    // 로그인 시도
    Protocol::SC_LOGIN loginPkt;

    if (pkt.bisdevlogin() == true || GSinstance->GetManager<DBManager>()->UserLoginCheck(pkt.user_name(), pkt.passwd()) == 0)
    {
        Protocol::hyps_user_info* user_info = new Protocol::hyps_user_info;

        user_info->set_id(session->GetSessionKey());

        user_info->set_name(pkt.user_name());
        
        if (pkt.bisdevlogin())
        {
            std::string dev_name = "dev" + std::to_string(session->GetSessionKey());
            user_info->set_name(dev_name);
            user_info->set_user_type(Protocol::hype_user::user_master);
            LOG_V("DEV_LOGIN %s", dev_name);
        }
        else
        {
            user_info->set_user_type(Protocol::hype_user::user_normal);
        }

        bool bret = Ginstance->GetManager<UserManager>()->AddUser(*user_info, session);

        loginPkt.set_allocated_user_info(user_info);
        loginPkt.set_success(bret); // TODO 체크

    }
    else // 불일치 등...
    {
        loginPkt.set_success(false); // TODO 체크
    }

    if (Ginstance->GetManager<SessionManager>()->OnLoginSession(session) == true)
    {
        SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(loginPkt);
        session->PreSend(sendBuffer); // TODO 직접호출이라 추후 변경해야함
    }
    return true;
}

bool CS_REGIST(HySessionRef& session, Protocol::CS_REGIST& pkt)
{
    Protocol::SC_REGIST registPkt;

    bool bResult = false;
    if(GSinstance->GetManager<DBManager>()->UserTableAdd(pkt.user_name(), pkt.passwd()) == 0)
    {
        bResult = true;
        registPkt.set_user_name(pkt.user_name());
    }
    registPkt.set_success(bResult); // TODO 체크

    SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(registPkt);
    session->PreSend(sendBuffer); // TODO 직접호출이라 추후 변경해야함

    return true;
}

bool CS_ENTER_GAME(HySessionRef& session, Protocol::CS_ENTER_GAME& pkt)
{

    // 신규 유저 정보 세팅
    Protocol::hyps_object_info MyObjectInfo;

    int64 player_id = pkt.player_id();
    float x = HyUtils::GetRandom(0.f, 100.f);
    float y = HyUtils::GetRandom(0.f, 100.f);
    float yaw = HyUtils::GetRandom(-360.f, 360.f);

    // 신규유저 구조체 세팅
    Protocol::hyps_pos_info pos_info;
    pos_info.set_object_id(player_id);
    pos_info.set_x(x);
    pos_info.set_y(y);
    pos_info.set_z(0);
    pos_info.set_yaw(yaw);

    MyObjectInfo.set_object_id(player_id);
    MyObjectInfo.set_object_type(Protocol::hype_object_type::creature);
    *(MyObjectInfo.mutable_pos_info()) = pos_info;


    UserManagerRef userManager = Ginstance->GetManager<UserManager>();

    if (userManager == nullptr)
    {
        return false;
    }



    // 신규 유저에게 기존 유저 정보 전달
    {
        //(Before My Player Add)
        Protocol::SC_SPAWN spawnPkt;

        const std::unordered_map<int64, UserRef>& AllUsers = userManager->GetAllUsers();
        for (const auto& userPair : AllUsers)
        {
            if (userPair.second && userPair.second->Get_bHasPlayerInfo())
            {
                if (player_id != userPair.first)
                {
                    const Protocol::hyps_object_info& existingPlayerInfo = userPair.second->Get_player_infoRef();

                    Protocol::hyps_object_info* existingPlayerObjectInfo = spawnPkt.add_players();
                    existingPlayerObjectInfo->set_object_id(existingPlayerInfo.object_id());
                    existingPlayerObjectInfo->set_object_type(existingPlayerInfo.object_type());
                    *(existingPlayerObjectInfo->mutable_pos_info()) = existingPlayerInfo.pos_info();
                }

            }
        }
        SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(spawnPkt);
        session->PreSend(sendBuffer);
    }

    // 기존 유저에게 신규유저 생성정보 전달
    {
        //(Before My Player Add)
        Protocol::BC_SPAWN bc_spawnPkt;
        Protocol::hyps_object_info* broadcastNewPlayerInfo = bc_spawnPkt.add_players();
        broadcastNewPlayerInfo->set_object_id(player_id);
        broadcastNewPlayerInfo->set_object_type(Protocol::hype_object_type::creature);
        *(broadcastNewPlayerInfo->mutable_pos_info()) = pos_info;

        SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(bc_spawnPkt);
        userManager->Broadcast(sendBuffer, player_id);
    }

    // 신규 유저에게 자기 자신 spawn 
    {
        //(My Player Add)
        Protocol::SC_ENTER_GAME enterGamePkt;
        *(enterGamePkt.mutable_my_player()) = pos_info;

        if (userManager->AddPlayerInfo(player_id, MyObjectInfo))
        {
            enterGamePkt.set_success(true);
        }
        else
        {
            return false;
        }

        SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
        session->PreSend(sendBuffer);
    }

    return true;
}

bool CS_LEAVE_GAME(HySessionRef& session, Protocol::CS_LEAVE_GAME& pkt)
{
    UserManagerRef userManager = Ginstance->GetManager<UserManager>();

    if (userManager == nullptr)
    {
        return false;
    }

    int64 sessionKey = session->GetSessionKey();
    UserRef User = userManager->GetUser(sessionKey);

    if (User == nullptr)
    {
        return false;
    }


    int64 obj_id = User->Get_player_infoRef().object_id();
    userManager->RemoveUse(session);

    Protocol::SC_LEAVE_GAME LeavePkt;
    SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(LeavePkt);
    session->PreSend(sendBuffer);

    Protocol::BC_DESPAWN despawnPkt;
    despawnPkt.add_object_ids(obj_id);

    sendBuffer = ServerPacketHandler::MakeSendBuffer(despawnPkt);
    userManager->Broadcast(sendBuffer);

    return true;
}

bool CS_MOVE_OBJECT(HySessionRef& session, Protocol::CS_MOVE_OBJECT& pkt)
{
    UserManagerRef userManager = Ginstance->GetManager<UserManager>();
    if (userManager == nullptr)
    {
        return false;
    }

    Protocol::SC_MOVE_OBJECT moveObjPkt;

    Protocol::hyps_object_info obj_info = pkt.move_info();
    // TODO 검증 Check
    
    *(moveObjPkt.mutable_move_info()) = obj_info;

    SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(moveObjPkt);
    userManager->Broadcast(sendBuffer);

    return true;
}

bool CS_ENTER_ROOM(HySessionRef& session, Protocol::CS_ENTER_ROOM& pkt)
{
    Protocol::SC_ENTER_ROOM enterPkt;

    if (session)
    {
        if (UserRef user = GSinstance->GetManager<UserManager>()->GetUser(pkt.userid()))
        {
            // 기존유저에 입장알림.
            Protocol::BC_ENTER_ROOM_OTHERS othersPkt;
            Protocol::hyps_user_info* user_info = othersPkt.add_users();
            *user_info = user->Get_user_infoRef();
            othersPkt.set_success(true);
            auto sendBuffer = ServerPacketHandler::MakeSendBuffer(othersPkt);
            GSinstance->Get_room()->DoAsync([=] { GSinstance->Get_room()->Broadcast(sendBuffer); });

            // 신규 유저 입장

            // 기존 room 유저정보 넣음
            std::vector<UserRef> users;
            GSinstance->Get_room()->SetUserList(users);
            for (int32 i = 0; i < users.size(); ++i)
            {
                Protocol::hyps_user_info* user_info = enterPkt.add_users();
                *user_info = users[i]->Get_user_infoRef();
            }

            GSinstance->Get_room()->Enter(user);
            enterPkt.set_success(true);
            sendBuffer = ServerPacketHandler::MakeSendBuffer(enterPkt);
            GSinstance->Get_room()->DoAsync([=] { session->PreSend(sendBuffer); });

            return true;
        }

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterPkt);
        GSinstance->Get_room()->DoAsync([=] { session->PreSend(sendBuffer); });
    }
    return true;
}

bool CS_CHAT(HySessionRef& session, Protocol::CS_CHAT& pkt)
{
    LOG_V("CS_CHAT %s", pkt.msg());

    // 노티
    // TODO broadcast할때.. sendhande을 좀 더 간편하게 이용하도록..
    Protocol::BC_GL_CHAT chatPkt;
    UserRef User = GSinstance->GetManager<UserManager>()->GetUser(session->GetSessionKey());
    if (User)
    {
        std::string userName = User->Get_user_infoRef().name();
        chatPkt.set_msg(userName + " : " +pkt.msg());
        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
        GSinstance->Get_room()->DoAsync([=] { GSinstance->Get_room()->Broadcast(sendBuffer); });
    }
    else
    {
        //error
        // send only session
    }

    return true;
}

bool CS_ECHO(HySessionRef& session, Protocol::CS_ECHO& pkt)
{
    // 노티
    Protocol::BC_GL_ECHO chatPkt;
    UserRef User = GSinstance->GetManager<UserManager>()->GetUser(session->GetSessionKey());
    if (User)
    {
        std::string userName = __FUNCTION__  + User->Get_user_infoRef().name();
        LOG_V("%s, %s", userName, pkt.msg());
        chatPkt.set_msg(userName + " : " + GSinstance->GetManager<TimeManager>()->GetCurrentTimeAsString());
        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
        GSinstance->Get_room()->DoAsync([=] { GSinstance->Get_room()->Broadcast(sendBuffer); });
    }
    else
    {
        //error
        // send only session
    }

    return true;
}
