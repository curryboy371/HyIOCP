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
	PKE_SC_ENTER_ROOM_OTHERS = 1006,
	PKE_CS_CHAT = 1007,
	PKE_SC_CHAT = 1008,
	PKE_BC_GL_CHAT = 1009,
	PKE_CS_ECHO = 1010,
	PKE_BC_GL_ECHO = 1011,
};

// Custom Handlers
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len);
bool CS_LOGIN(HySessionRef& session, Protocol::CS_LOGIN& pkt);
bool CS_REGIST(HySessionRef& session, Protocol::CS_REGIST& pkt);
bool CS_ENTER_ROOM(HySessionRef& session, Protocol::CS_ENTER_ROOM& pkt);
bool CS_CHAT(HySessionRef& session, Protocol::CS_CHAT& pkt);
bool CS_ECHO(HySessionRef& session, Protocol::CS_ECHO& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
		{
			GPacketHandler[i] = INVALID_PACKET;
		}
		GPacketHandler[PKE_CS_LOGIN] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::CS_LOGIN > (CS_LOGIN, "CS_LOGIN", static_cast<uint16>(PKE_CS_LOGIN), session, buffer, len); };
		GPacketHandler[PKE_CS_REGIST] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::CS_REGIST > (CS_REGIST, "CS_REGIST", static_cast<uint16>(PKE_CS_REGIST), session, buffer, len); };
		GPacketHandler[PKE_CS_ENTER_ROOM] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::CS_ENTER_ROOM > (CS_ENTER_ROOM, "CS_ENTER_ROOM", static_cast<uint16>(PKE_CS_ENTER_ROOM), session, buffer, len); };
		GPacketHandler[PKE_CS_CHAT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::CS_CHAT > (CS_CHAT, "CS_CHAT", static_cast<uint16>(PKE_CS_CHAT), session, buffer, len); };
		GPacketHandler[PKE_CS_ECHO] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::CS_ECHO > (CS_ECHO, "CS_ECHO", static_cast<uint16>(PKE_CS_ECHO), session, buffer, len); };
	}

	static bool HandlePacket(HySessionRef& session, BYTE * buffer, int32 len)
	{
		FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
		return GPacketHandler[header->PacketID](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::SC_LOGIN& pkt) { return MakeSendBuffer(pkt, PKE_SC_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::SC_REGIST& pkt) { return MakeSendBuffer(pkt, PKE_SC_REGIST); }
	static SendBufferRef MakeSendBuffer(Protocol::SC_ENTER_ROOM& pkt) { return MakeSendBuffer(pkt, PKE_SC_ENTER_ROOM); }
	static SendBufferRef MakeSendBuffer(Protocol::SC_ENTER_ROOM_OTHERS& pkt) { return MakeSendBuffer(pkt, PKE_SC_ENTER_ROOM_OTHERS); }
	static SendBufferRef MakeSendBuffer(Protocol::SC_CHAT& pkt) { return MakeSendBuffer(pkt, PKE_SC_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::BC_GL_CHAT& pkt) { return MakeSendBuffer(pkt, PKE_BC_GL_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::BC_GL_ECHO& pkt) { return MakeSendBuffer(pkt, PKE_BC_GL_ECHO); }

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
			FString strPacketID = FString::Printf(TEXT("(%d)"), packet_id);
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
		//ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};