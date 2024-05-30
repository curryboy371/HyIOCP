#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"

#include "UserManager.h"
#include "User.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

/* 클라이언트 side 패킷 수신 */

/* 컨텐츠 수동 작업 */
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    std::cout << "\nINVALID_PACKET:: id " << header->id << std::endl;

    return false;
}

bool SC_LOGIN(HySessionRef& session, Protocol::SC_LOGIN& pkt)
{
    if (pkt.success() == true)
    {
        UserRef user = std::make_shared<User>();
        user->SetUserID(pkt.userid());
        Ginstance->GetManager<UserManager>()->Set_myUser(user);

        std::cout << "SC_LOGIN:: login success user id-" << user->GetUserID() << std::endl;

        session->SetSessionStatus(E_SESSION_STATUS::E_LOGIN_STATUS);

        // 방 입장 시도
        Protocol::CS_ENTER_ROOM enterPkt;
        enterPkt.set_room_name("test room");
        enterPkt.set_userid(user->GetUserID());
        SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPkt);
        session->PreSend(sendBuffer);

        std::cout << "SC_LOGIN:: try enter the room - " << enterPkt.room_name() << std::endl;

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

        }
    }

    return true;
}

bool SC_CHAT(HySessionRef& session, Protocol::SC_CHAT& pkt)
{
    std::cout << pkt.msg() << std::endl;

    return true;
}

bool BC_GL_CHAT(HySessionRef& session, Protocol::BC_GL_CHAT& pkt)
{
    std::cout << pkt.msg() << std::endl;

    return true;
}
