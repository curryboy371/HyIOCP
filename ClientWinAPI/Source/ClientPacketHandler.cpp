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
    FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
    DLOG_V("INVALID_PACKET", header->PacketID);
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

        GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_LOGIN, 0);
        DLOG_V("SC_LOGIN:: login success user", user->Get_user_infoRef().name());

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
        GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_LOGIN, 1);
        DLOG("SC_LOGIN false!!!");
    }

    return true;
}

bool SC_REGIST(HySessionRef& session, Protocol::SC_REGIST& pkt)
{
    if (pkt.success() == true)
    {
        GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_REGIST, 0);
        DLOG_V("SC_REGIST:: sucess user : ", pkt.user_name());
    }
    else
    {
        GCinstance->GetManager<NetworkManager>()->CallnetworkCB(HyPacketID::PKE_SC_REGIST, 1);
        DLOG("SC_REGIST false!!!");
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
            UserRef myUser = GCinstance->GetManager<UserManager>()->GetMyUser(session->GetSessionKey());

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

bool BC_ENTER_ROOM_OTHERS(HySessionRef& session, Protocol::BC_ENTER_ROOM_OTHERS& pkt)
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
