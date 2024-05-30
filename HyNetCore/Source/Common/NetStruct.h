#pragma once

class HySession;

struct OverlappedEx : public OVERLAPPED
{
    OverlappedEx() : IOtype(E_IO_TYPE::E_IO_TYPE_MAX), byteSize(0)
    {
        ZeroMemory(static_cast<OVERLAPPED*>(this), sizeof(OVERLAPPED));
    }

    void Init()
    {
        ZeroMemory(static_cast<OVERLAPPED*>(this), sizeof(OVERLAPPED));
        sessionRef.reset();
        byteSize = 0;
    }

    void ResetOwner()
    {
        sessionRef.reset();
    }

    const DWORD& GetByteSize() const
    {
        return byteSize;
    }

    void SetBytes(const DWORD& inByteSize)
    {
        byteSize = inByteSize;
    }

    void SetOwnerSessionRef(const std::shared_ptr<HySession>& InsessionRef)
    {
        sessionRef = InsessionRef;
    }

    void SetIOType(E_IO_TYPE inType)
    {
        IOtype = inType;
    }

    std::shared_ptr<HySession> GetOwnerSessionRef() const
    {
        return sessionRef;
    }

    E_IO_TYPE GetIOType() const
    {
        return IOtype;
    }

private:
    std::shared_ptr<HySession> sessionRef; // overlapped 구조체로 session과 overlapped를 모두 접근 가능하도록
    E_IO_TYPE IOtype;
    DWORD byteSize;


};