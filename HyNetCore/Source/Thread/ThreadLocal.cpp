#include "Netpch.h"

#include "ThreadLocal.h"

thread_local int32 tlsThreadID = 0;
thread_local std::shared_ptr<class SendBufferChunk> tlsSendBufferChunk;

thread_local class JobQueue* tlsCurJobQueue = nullptr;
thread_local unsigned long long tlsEndTickCount = 0;