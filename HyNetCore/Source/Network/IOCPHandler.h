#pragma once


class IOCPHandler
{
public:
    static bool OnAccept(HySessionRef sessionRef, OverlappedEx* overlapped);
    static bool OnConnect(HySessionRef sessionRef, OverlappedEx* overlapped);
    static bool OnReceive(HySessionRef sessionRef, OverlappedEx* overlapped);
    static bool OnSend(HySessionRef sessionRef, OverlappedEx* overlapped);
    static bool OnDisconnect(HySessionRef sessionRef, OverlappedEx* overlapped);
};

