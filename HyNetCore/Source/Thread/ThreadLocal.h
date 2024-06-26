#pragma once


/* Thread Local */

/* 
	thread local로 들고 있을 전역 변수를 이 위치에서 선언함.
	접두사는 tls변수명을 사용함. ( Thread_Local_Storage ) 
*/

extern thread_local int32 tlsThreadID;
extern thread_local std::shared_ptr<class SendBufferChunk> tlsSendBufferChunk;

extern thread_local class JobQueue* tlsCurJobQueue;
extern thread_local unsigned long long tlsEndTickCount;
