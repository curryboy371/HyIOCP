#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"

#include "NetworkManager.h"
#include "SessionManager.h"
#include "UserManager.h"
#include "User.h"

#include "Room.h"

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
        user->Set_user_info(pkt.user_info());
        user->Set_ownerSession(session);

        GCinstance->GetManager<UserManager>()->AddClientSession(user);

        GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_LOGIN);
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
        DLOG("SC_LOGIN false!!!");
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
            // 본인 입장
            UserRef myUser = GCinstance->GetManager<UserManager>()->GetMyUser();

            // 신규 유저 입장 (본인 ) 
            GCinstance->Get_room()->Enter(myUser);

            for (int32 i = 0; i < pkt.users_size(); ++i)
            {
                int64 userid = pkt.users()[i].id();
                //HySessionRef otherSession = GCinstance->GetManager<Client::SessionManager>()->GetUserSession(userid); //다른 유저 세션은 보관 안함
                if(Ginstance->GetManager<UserManager>()->AddUser(pkt.users()[i], nullptr))
                {
                    UserRef newUser=  Ginstance->GetManager<UserManager>()->GetUser(pkt.users()[i].id());
                    std::string username = pkt.users()[i].name();
                    // 기존 유저정보
                    GCinstance->Get_room()->Enter(newUser);
                }
            }

            std::string msg = myUser->Get_user_infoRef().name() + " : Enter the room (me)";
            AddTextToOutput(msg);
        }
    }

    return true;
}

bool SC_ENTER_ROOM_OTHERS(HySessionRef& session, Protocol::SC_ENTER_ROOM_OTHERS& pkt)
{
    if (session)
    {
        bool bsuccess = pkt.success();

        if (bsuccess)
        {
            for (int32 i = 0; i < pkt.users_size(); ++i)
            {
                int64 userid = pkt.users()[i].id();
                //HySessionRef otherSession = GCinstance->GetManager<Client::SessionManager>()->GetUserSession(userid);
                if (Ginstance->GetManager<UserManager>()->AddUser(pkt.users()[i], nullptr))
                {
                    UserRef newUser = Ginstance->GetManager<UserManager>()->GetUser(pkt.users()[i].id());

                    // 신규 유저 입장 ( 다른유저 ) 
                    GCinstance->Get_room()->Enter(newUser);
                    std::string msg = newUser->Get_user_infoRef().name() + " : Enter the room";
                    AddTextToOutput(msg);
                }
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
    AddTextToOutput(pkt.msg());

    return true;
}

bool BC_GL_ECHO(HySessionRef& session, Protocol::BC_GL_ECHO& pkt)
{
    PRINT_V("BC_GL_ECHO", pkt.msg());
    AddTextToOutput(pkt.msg());
    return true;
}
