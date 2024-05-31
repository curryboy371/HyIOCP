#include "Netpch.h"
#include "SendBuffer.h"


SendBufferChunk::SendBufferChunk()
	:buffer(), bopen(false), usedSize(0)
{
}

SendBufferChunk::~SendBufferChunk()
{

}

void SendBufferChunk::Reset()
{
	bopen = false;
	usedSize = 0;
}

SendBufferRef SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(bopen == false);

	if (allocSize > FreeSize())
	{
		return nullptr;
	}

	bopen = true;

	// 여기서 sharedptr 새로 만드는게 아닌지 체크.
	// 기존걸 레퍼런스 카운트 늘리는 식으로 사용해야해.
	// 실제 여기는 새로 복사해서 쓰는거 아님?
	return std::make_shared<SendBuffer>(shared_from_this(), Buffer(), allocSize);
}

void SendBufferChunk::Close(uint32 writeSize)
{

	ASSERT_CRASH(bopen == true);
	bopen = false;
	usedSize += writeSize;

}


SendBuffer::SendBuffer(SendBufferChunkRef inowner, BYTE* inbuffer, int32 inbufferSize)
	:owner(inowner), buffer(inbuffer), allocSize(inbufferSize)
{
	// 버퍼 사이즈 설정해주고
}

SendBuffer::~SendBuffer()
{

}

void SendBuffer::Close(uint32 inwriteSize)
{
	ASSERT_CRASH(allocSize >= inwriteSize);
	writeSize = inwriteSize;
	owner->Close(writeSize);

}

SendBufferRef SendBufferManager::Open(uint32 size)
{
	// 쓰레드마다 가지고 있는 자원이므로 경합없음.
	if (tlsSendBufferChunk == nullptr)
	{
		tlsSendBufferChunk = Pop();
	}

	ASSERT_CRASH(tlsSendBufferChunk->IsOpen() == false );

	// 다 썼으면 버리고 새로 교체함.
	if (tlsSendBufferChunk->FreeSize() < size)
	{
		tlsSendBufferChunk = Pop();
		tlsSendBufferChunk->Reset();
	}

	//std::cout << "\nFREE : ID-" << LThreadId<< " Size-" << tlsSendBufferChunk->FreeSize() << " Len-" << GetBufferChunkCount();

	return tlsSendBufferChunk->Open(size);
}

SendBufferChunkRef SendBufferManager::Pop()
{
	// 버퍼를 꺼내 씀
	{
		// WRITE_LOCK
		USE_MULOCK;

		if (sendBufferChunks.empty() == false)
		{
			SendBufferChunkRef sendBufferChunk = sendBufferChunks.back();
			sendBufferChunks.pop_back();
			return sendBufferChunk;
		}

	}

	// 여유분이 없으면 새로 생성
	// 레퍼런스카운트가 0이되면 delete가 호출되지 않고 PushGlobal이 호출됨
	// 객체와 별개로 유일하게 동작해야하므로  static 함수임

	return std::shared_ptr<SendBufferChunk>(new SendBufferChunk, PushGlobal);
}

void SendBufferManager::Push(SendBufferChunkRef buffer)
{
	// 버퍼에 추가
	// WRITE_LOCK
	USE_MULOCK;

	sendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	// 반납한 버퍼 재사용
	Ginstance->Get_sendBufferMgr()->Push(SendBufferChunkRef(buffer, PushGlobal));
}
