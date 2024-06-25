#pragma once
#include "Protocol.pb.h"

#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
#define UE_PRO 1
#endif

#if UE_PRO
#include "Hy.h"
#endif


using PacketHandlerFunc = std::function<bool(HySessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum HyPacketID : uint16
{
	PKE_CS_LOGIN = 1000,
	PKE_SC_LOGIN = 1001,
	PKE_CS_REGIST = 1002,
	PKE_SC_REGIST = 1003,
	PKE_CS_ENTER_ROOM = 1004,
	PKE_SC_ENTER_ROOM = 1005,
	PKE_BC_ENTER_ROOM_OTHERS = 1006,
	PKE_CS_ENTER_GAME = 1007,
	PKE_SC_ENTER_GAME = 1008,
	PKE_CS_LEAVE_GAME = 1009,
	PKE_SC_LEAVE_GAME = 1010,
	PKE_BC_LEAVE_GAME = 1011,
	PKE_SC_SPAWN = 1012,
	PKE_BC_SPAWN = 1013,
	PKE_SC_DESPAWN = 1014,
	PKE_BC_DESPAWN = 1015,
	PKE_CS_MOVE_OBJECT = 1016,
	PKE_SC_MOVE_OBJECT = 1017,
	PKE_CS_CHAT = 1018,
	PKE_SC_CHAT = 1019,
	PKE_BC_GL_CHAT = 1020,
	PKE_CS_ECHO = 1021,
	PKE_BC_GL_ECHO = 1022,
};

// Custom Handlers
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len);
bool SC_LOGIN(HySessionRef& session, Protocol::SC_LOGIN& pkt);
bool SC_REGIST(HySessionRef& session, Protocol::SC_REGIST& pkt);
bool SC_ENTER_ROOM(HySessionRef& session, Protocol::SC_ENTER_ROOM& pkt);
bool BC_ENTER_ROOM_OTHERS(HySessionRef& session, Protocol::BC_ENTER_ROOM_OTHERS& pkt);
bool SC_ENTER_GAME(HySessionRef& session, Protocol::SC_ENTER_GAME& pkt);
bool SC_LEAVE_GAME(HySessionRef& session, Protocol::SC_LEAVE_GAME& pkt);
bool BC_LEAVE_GAME(HySessionRef& session, Protocol::BC_LEAVE_GAME& pkt);
bool SC_SPAWN(HySessionRef& session, Protocol::SC_SPAWN& pkt);
bool BC_SPAWN(HySessionRef& session, Protocol::BC_SPAWN& pkt);
bool SC_DESPAWN(HySessionRef& session, Protocol::SC_DESPAWN& pkt);
bool BC_DESPAWN(HySessionRef& session, Protocol::BC_DESPAWN& pkt);
bool SC_MOVE_OBJECT(HySessionRef& session, Protocol::SC_MOVE_OBJECT& pkt);
bool SC_CHAT(HySessionRef& session, Protocol::SC_CHAT& pkt);
bool BC_GL_CHAT(HySessionRef& session, Protocol::BC_GL_CHAT& pkt);
bool BC_GL_ECHO(HySessionRef& session, Protocol::BC_GL_ECHO& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
		{
			GPacketHandler[i] = INVALID_PACKET;
		}
		GPacketHandler[PKE_SC_LOGIN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_LOGIN > (SC_LOGIN, "SC_LOGIN", static_cast<uint16>(PKE_SC_LOGIN), session, buffer, len); };
		GPacketHandler[PKE_SC_REGIST] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_REGIST > (SC_REGIST, "SC_REGIST", static_cast<uint16>(PKE_SC_REGIST), session, buffer, len); };
		GPacketHandler[PKE_SC_ENTER_ROOM] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_ENTER_ROOM > (SC_ENTER_ROOM, "SC_ENTER_ROOM", static_cast<uint16>(PKE_SC_ENTER_ROOM), session, buffer, len); };
		GPacketHandler[PKE_BC_ENTER_ROOM_OTHERS] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_ENTER_ROOM_OTHERS > (BC_ENTER_ROOM_OTHERS, "BC_ENTER_ROOM_OTHERS", static_cast<uint16>(PKE_BC_ENTER_ROOM_OTHERS), session, buffer, len); };
		GPacketHandler[PKE_SC_ENTER_GAME] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_ENTER_GAME > (SC_ENTER_GAME, "SC_ENTER_GAME", static_cast<uint16>(PKE_SC_ENTER_GAME), session, buffer, len); };
		GPacketHandler[PKE_SC_LEAVE_GAME] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_LEAVE_GAME > (SC_LEAVE_GAME, "SC_LEAVE_GAME", static_cast<uint16>(PKE_SC_LEAVE_GAME), session, buffer, len); };
		GPacketHandler[PKE_BC_LEAVE_GAME] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_LEAVE_GAME > (BC_LEAVE_GAME, "BC_LEAVE_GAME", static_cast<uint16>(PKE_BC_LEAVE_GAME), session, buffer, len); };
		GPacketHandler[PKE_SC_SPAWN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_SPAWN > (SC_SPAWN, "SC_SPAWN", static_cast<uint16>(PKE_SC_SPAWN), session, buffer, len); };
		GPacketHandler[PKE_BC_SPAWN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_SPAWN > (BC_SPAWN, "BC_SPAWN", static_cast<uint16>(PKE_BC_SPAWN), session, buffer, len); };
		GPacketHandler[PKE_SC_DESPAWN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_DESPAWN > (SC_DESPAWN, "SC_DESPAWN", static_cast<uint16>(PKE_SC_DESPAWN), session, buffer, len); };
		GPacketHandler[PKE_BC_DESPAWN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_DESPAWN > (BC_DESPAWN, "BC_DESPAWN", static_cast<uint16>(PKE_BC_DESPAWN), session, buffer, len); };
		GPacketHandler[PKE_SC_MOVE_OBJECT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_MOVE_OBJECT > (SC_MOVE_OBJECT, "SC_MOVE_OBJECT", static_cast<uint16>(PKE_SC_MOVE_OBJECT), session, buffer, len); };
		GPacketHandler[PKE_SC_CHAT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_CHAT > (SC_CHAT, "SC_CHAT", static_cast<uint16>(PKE_SC_CHAT), session, buffer, len); };
		GPacketHandler[PKE_BC_GL_CHAT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_GL_CHAT > (BC_GL_CHAT, "BC_GL_CHAT", static_cast<uint16>(PKE_BC_GL_CHAT), session, buffer, len); };
		GPacketHandler[PKE_BC_GL_ECHO] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_GL_ECHO > (BC_GL_ECHO, "BC_GL_ECHO", static_cast<uint16>(PKE_BC_GL_ECHO), session, buffer, len); };
	}

	static bool HandlePacket(HySessionRef& session, BYTE * buffer, int32 len)
	{
		FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
		return GPacketHandler[header->PacketID](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::CS_LOGIN& pkt) { return MakeSendBuffer(pkt, PKE_CS_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_REGIST& pkt) { return MakeSendBuffer(pkt, PKE_CS_REGIST); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_ENTER_ROOM& pkt) { return MakeSendBuffer(pkt, PKE_CS_ENTER_ROOM); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_ENTER_GAME& pkt) { return MakeSendBuffer(pkt, PKE_CS_ENTER_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_LEAVE_GAME& pkt) { return MakeSendBuffer(pkt, PKE_CS_LEAVE_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_MOVE_OBJECT& pkt) { return MakeSendBuffer(pkt, PKE_CS_MOVE_OBJECT); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_CHAT& pkt) { return MakeSendBuffer(pkt, PKE_CS_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_ECHO& pkt) { return MakeSendBuffer(pkt, PKE_CS_ECHO); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, const std::string funcName, uint16 packet_id, HySessionRef& session, BYTE * buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(FPacketHeader), len - sizeof(FPacketHeader)) == false)
			return false;

#ifdef UE_PRO
	#if UE_BUILD_SHIPPING > 0

	#else
			FString strPacketID = FString::Printf(TEXT("[PacketID(%d)]"), packet_id);
			LOG_GUARD_STR(strPacketID);
	#endif
			bool bret = func(session, pkt);
	#else
	#ifdef DETAIL_LOG
			std::cout << "[Start] " << funcName << "(" << packet_id << ")" << std::endl;
			bool bret = func(session, pkt);
			std::cout << "[End] " << funcName << "(" << packet_id << ")" << " ret : " << bret << std::endl;
	#else
			bool bret = func(session, pkt);
	#endif
#endif

		return bret;
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T & pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(FPacketHeader);


#if UE_PRO
		SendBufferRef sendBuffer = MakeShared<SendBuffer>(packetSize);
#else
		SendBufferRef sendBuffer = Ginstance->Get_sendBufferMgr()->Open(packetSize);
#endif
		FPacketHeader* header = reinterpret_cast<FPacketHeader*>(sendBuffer->Buffer());
		header->PacketSize = packetSize;
		header->PacketID = pktId;
		pkt.SerializeToArray(&header[1], dataSize);
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};