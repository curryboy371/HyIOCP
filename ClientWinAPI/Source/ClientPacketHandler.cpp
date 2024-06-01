#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"

#include "UserManager.h"
#include "User.h"

#include "../ClientWinAPI.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

/* 클라이언트 side 패킷 수신 */

/* 컨텐츠 수동 작업 */
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    DLOG_V("INVALID_PACKET", header->id);
    return false;
}

bool SC_LOGIN(HySessionRef& session, Protocol::SC_LOGIN& pkt)
{
    if (pkt.success() == true)
    {
        UserRef user = std::make_shared<User>();
        user->SetUserID(pkt.userid());

        Protocol::hyps_user_info myInfo;
        std::string my_name = session->Get_socketName() + std::to_string(pkt.userid());
        myInfo.set_name(my_name);
        myInfo.set_id(pkt.userid());
        user->Set_user_info(myInfo);
        user->Set_ownerSession(session);

        GCinstance->GetManager<UserManager>()->Set_myUser(user);

        DLOG_V("SC_LOGIN:: login success user id-", user->GetUserID());

        session->SetSessionStatus(E_SESSION_STATUS::E_LOGIN_STATUS);

        // 방 입장 시도
        Protocol::CS_ENTER_ROOM enterPkt;
        enterPkt.set_room_name("test room");
        enterPkt.set_userid(user->GetUserID());
        SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPkt);

        session->PreSend(sendBuffer);

        DLOG_V("SC_LOGIN:: try enter the room - ", enterPkt.room_name());

    }
    else
    {
        // retry
    }
    return true;
}

bool SC_ENTER_ROOM(HySessionRef& session, Protocol::SC_ENTER_ROOM& pkt)
{
    if (session)
    {
        bool bsuccess = pkt.success();

        if (bsuccess)
        {
            for (int32 i = 0; i < pkt.users_size(); ++i)
            {
                bool bret = Ginstance->GetManager<UserManager>()->AddUser(pkt.users()[i], session);
            }
        }
    }

    return true;
}

bool SC_CHAT(HySessionRef& session, Protocol::SC_CHAT& pkt)
{
    PRINT_V("SC_CHAT", pkt.msg());
    AddTextToOutput(pkt.msg());
    return true;
}

bool BC_GL_CHAT(HySessionRef& session, Protocol::BC_GL_CHAT& pkt)
{
    PRINT_V("BC_GL_CHAT", pkt.msg());

    hEditOutput;

    AddTextToOutput(pkt.msg());

    return true;
}
