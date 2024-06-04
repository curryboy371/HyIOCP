#pragma once
#include "Protocol.pb.h"

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
bool SC_LOGIN(HySessionRef& session, Protocol::SC_LOGIN& pkt);
bool SC_REGIST(HySessionRef& session, Protocol::SC_REGIST& pkt);
bool SC_ENTER_ROOM(HySessionRef& session, Protocol::SC_ENTER_ROOM& pkt);
bool SC_ENTER_ROOM_OTHERS(HySessionRef& session, Protocol::SC_ENTER_ROOM_OTHERS& pkt);
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
		GPacketHandler[PKE_SC_ENTER_ROOM_OTHERS] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_ENTER_ROOM_OTHERS > (SC_ENTER_ROOM_OTHERS, "SC_ENTER_ROOM_OTHERS", static_cast<uint16>(PKE_SC_ENTER_ROOM_OTHERS), session, buffer, len); };
		GPacketHandler[PKE_SC_CHAT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::SC_CHAT > (SC_CHAT, "SC_CHAT", static_cast<uint16>(PKE_SC_CHAT), session, buffer, len); };
		GPacketHandler[PKE_BC_GL_CHAT] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_GL_CHAT > (BC_GL_CHAT, "BC_GL_CHAT", static_cast<uint16>(PKE_BC_GL_CHAT), session, buffer, len); };
		GPacketHandler[PKE_BC_GL_ECHO] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::BC_GL_ECHO > (BC_GL_ECHO, "BC_GL_ECHO", static_cast<uint16>(PKE_BC_GL_ECHO), session, buffer, len); };
	}

	static bool HandlePacket(HySessionRef& session, BYTE * buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::CS_LOGIN& pkt) { return MakeSendBuffer(pkt, PKE_CS_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_REGIST& pkt) { return MakeSendBuffer(pkt, PKE_CS_REGIST); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_ENTER_ROOM& pkt) { return MakeSendBuffer(pkt, PKE_CS_ENTER_ROOM); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_CHAT& pkt) { return MakeSendBuffer(pkt, PKE_CS_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::CS_ECHO& pkt) { return MakeSendBuffer(pkt, PKE_CS_ECHO); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, const std::string funcName, uint16 packet_id, HySessionRef& session, BYTE * buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

#ifdef DETAIL_LOG
		std::cout << "[Start] " << funcName << "("<< packet_id <<")" << std::endl;
		bool bret = func(session, pkt);
		std::cout << "[End] " << funcName << "(" << packet_id << ")" << " ret : " << bret << std::endl;
#else
		bool bret = func(session, pkt);
#endif

		return bret;
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T & pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = Ginstance->Get_sendBufferMgr()->Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};