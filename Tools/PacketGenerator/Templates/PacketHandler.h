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
{%- for pkt in parser.total_pkt %}
	PKE_{{pkt.name}} = {{pkt.id}},
{%- endfor %}
};

// Custom Handlers
bool INVALID_PACKET(HySessionRef& session, BYTE* buffer, int32 len);

{%- for pkt in parser.recv_pkt %}
bool {{pkt.name}}(HySessionRef& session, Protocol::{{pkt.name}}& pkt);
{%- endfor %}

class {{output}}
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
		{
			GPacketHandler[i] = INVALID_PACKET;
		}

{%- for pkt in parser.recv_pkt %}
		GPacketHandler[PKE_{{pkt.name}}] = [](HySessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::{{pkt.name}} > ({{pkt.name}}, "{{pkt.name}}", static_cast<uint16>(PKE_{{pkt.name}}), session, buffer, len); };
{%- endfor %}
	}

	static bool HandlePacket(HySessionRef& session, BYTE * buffer, int32 len)
	{
		FPacketHeader* header = reinterpret_cast<FPacketHeader*>(buffer);
		return GPacketHandler[header->PacketID](session, buffer, len);
	}

{%- for pkt in parser.send_pkt %}
	static SendBufferRef MakeSendBuffer(Protocol::{{pkt.name}}& pkt) { return MakeSendBuffer(pkt, PKE_{{pkt.name}}); }
{%- endfor %}

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