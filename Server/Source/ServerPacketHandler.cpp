#pragma once
#include "pch.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"

#include "Room.h"
#include "User.h"

#include "SessionManager.h"


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

    Protocol::hyps_user_info user_info;
    user_info.set_id(session->GetSessionKey());
    user_info.set_name(pkt.user_name());
    user_info.set_user_type(Protocol::hype_user::user_normal);

    bool bret = Ginstance->GetManager<UserManager>()->AddUser(user_info, session);

    loginPkt.set_userid(user_info.id());
    loginPkt.set_success(bret); // TODO 체크

    if (bret)
    {
        if (Ginstance->GetManager<SessionManager>()->OnLoginSession(session) == true)
        {
            SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(loginPkt);
            session->PreSend(sendBuffer); // TODO 직접호출이라 추후 변경해야함
        }
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
            // 기존 room 유저정보 넣음
            std::vector<UserRef> users;
            GSinstance->Get_room()->SetUserList(users);
            for (int32 i = 0; i < users.size(); ++i)
            {
                Protocol::hyps_user_info* user_info = enterPkt.add_users();
                *user_info = users[i]->Get_user_infoRef();
            }

            // 신규 유저 입장
            GSinstance->Get_room()->Enter(user);
            enterPkt.set_success(true);


            // 노티
            // TODO broadcast할때.. sendhande을 좀 더 간편하게 이용하도록..
            Protocol::BC_GL_CHAT chatPkt;
            chatPkt.set_msg(u8"User Enter" + user->Get_user_infoRef().name());
            auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
            GSinstance->Get_room()->DoAsync([=] { GSinstance->Get_room()->Broadcast(sendBuffer); });
        }
    }

    SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(enterPkt);
    session->PreSend(sendBuffer); // TODO 직접호출이라 추후 변경해야함
    return true;
}

bool CS_CHAT(HySessionRef& session, Protocol::CS_CHAT& pkt)
{
    PRINT_V(CS_CHAT, pkt.msg());
    return true;
}
