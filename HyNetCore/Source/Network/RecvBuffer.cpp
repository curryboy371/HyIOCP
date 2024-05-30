#include "Netpch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 inBufferSize)
	:bufferSize(inBufferSize)
{
	// 버퍼 사이즈 설정
	// Clean()함수에서 memcpy로 버퍼를 복사하는 횟수를 최소화하기 위해 버퍼 사이즈를 크게 잡아둠.
	capacity = bufferSize * BUFFER_COUNT;
	buffer.resize(capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();
	if (dataSize == 0)
	{

		// read, write의 pos가 일치한다면 ( 읽을 버퍼가 없는 경우 ) 버퍼 초기화
		// 이미 사용된 데이터는 어차피 다시 덮어 쓰이고 사용되므로 지우진 않고 위치만 초기화
		readPos = writePos = 0; 
	}
	else
	{
		// 그렇지 않은 경우에는 ( 읽을 버퍼가 있는 경우 ) 
		// 버퍼의 시작 위치부터 읽어야하는 버퍼를 복사한다.
		// 이러한 복사가 실행되는 횟수를 최소화 해야함.

		// 여유공간이 버퍼 하나보다 줄어드는 경우 데이터 당기기
		if (FreeSize() < bufferSize)
		{
			std::memcpy(&buffer[0], &buffer[readPos], dataSize);
			readPos = 0;
			writePos = dataSize;
		}
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	if (numOfBytes > DataSize())
	{
		return false;
	}

	readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	if (numOfBytes > FreeSize())
	{
		return false;
	}

	writePos += numOfBytes;

	return true;
}

BYTE* RecvBuffer::ReadPos()
{
	return &buffer[readPos];
}

BYTE* RecvBuffer::WritePos()
{
	return &buffer[writePos];
}

int32 RecvBuffer::DataSize()
{
	// read가능 사이즈 반환

	int32 dataSize = writePos - readPos;
	return dataSize;
}

int32 RecvBuffer::FreeSize()
{
	// write 가능 사이즈 반환

	int32 freeSize = capacity - writePos;
	return freeSize;
}
