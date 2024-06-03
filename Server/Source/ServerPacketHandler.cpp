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
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    std::cout << "\nINVALID_PACKET:: id " << header->id << std::endl;
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
        user_info->set_user_type(Protocol::hype_user::user_normal);

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

bool CS_ENTER_ROOM(HySessionRef& session, Protocol::CS_ENTER_ROOM& pkt)
{
    Protocol::SC_ENTER_ROOM enterPkt;

    if (session)
    {
        if (UserRef user = GSinstance->GetManager<UserManager>()->GetUser(pkt.userid()))
        {
            // 기존유저에 입장알림.
            Protocol::SC_ENTER_ROOM_OTHERS othersPkt;
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
    PRINT_V("CS_CHAT", pkt.msg());

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
        PRINT_V(userName, pkt.msg());
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
