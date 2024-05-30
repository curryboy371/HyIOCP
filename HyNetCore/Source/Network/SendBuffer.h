#pragma once

class SendBufferChunk;

class SendBuffer : public std::enable_shared_from_this<SendBuffer>
{

public:
	SendBuffer(SendBufferChunkRef inowner, BYTE* inbuffer, int32 inbufferSize);
	~SendBuffer();


	BYTE* Buffer() { return buffer; }
	uint32 WriteSize() { return writeSize; }
	uint32 AllocSize() { return allocSize; }
	void Close(uint32 inwriteSize);

	//int32 Capacity() { return static_cast<int32>(_buffer.size()); }
	//void CopyData(void* data, int32 len);

private:
	//std::vector<BYTE> _buffer;
	BYTE* buffer;
	uint32 allocSize = 0;
	uint32 writeSize = 0;
	SendBufferChunkRef owner;

};


class SendBufferChunk : public std::enable_shared_from_this<SendBufferChunk>
{
	enum
	{
		//SEND_BUFFER_CHUNK_SIZE = 0x1000
		SEND_BUFFER_CHUNK_SIZE = 4096
	};

public:
	SendBufferChunk();
	~SendBufferChunk();

	void Reset();
	SendBufferRef Open(uint32 allocSize);
	void Close(uint32 writeSize);

	bool IsOpen() { return bopen; }
	BYTE* Buffer() { return &buffer[usedSize]; }
	//uint32 FreeSize() { return static_cast<uint32>(SEND_BUFFER_CHUNK_SIZE) - usedSize; }
	uint32 FreeSize() { return static_cast<uint32>(buffer.size()) - usedSize; }

private:
	std::array<BYTE, SEND_BUFFER_CHUNK_SIZE> buffer;
	//BYTE _buffer[SEND_BUFFER_CHUNK_SIZE];
	bool bopen = false;
	uint32 usedSize = 0;

};


class SendBufferManager : std::enable_shared_from_this<SendBufferManager>
{
	DEF_MUTEX

public:
	SendBufferRef Open(uint32 size);


public:
	int32 GetBufferChunkCount() { return static_cast<int32>(sendBufferChunks.size()); }
private:
	SendBufferChunkRef	Pop();
	void				Push(SendBufferChunkRef buffer);

	static void			PushGlobal(SendBufferChunk* buffer); // shared potr ref count 이 되면 이 함수를 호출하게 하여 static 함수.

	

private:
	std::vector<SendBufferChunkRef> sendBufferChunks;

};