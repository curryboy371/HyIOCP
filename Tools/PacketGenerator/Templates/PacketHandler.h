#pragma once
#include "Protocol.pb.h"

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
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}

{%- for pkt in parser.send_pkt %}
	static SendBufferRef MakeSendBuffer(Protocol::{{pkt.name}}& pkt) { return MakeSendBuffer(pkt, PKE_{{pkt.name}}); }
{%- endfor %}

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