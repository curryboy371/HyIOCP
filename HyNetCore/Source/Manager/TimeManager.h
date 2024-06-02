#pragma once

#include "BaseManager.h"
#include <ctime>
#include <iomanip>
#include <sstream>

class TimeManager : public BaseManager
{
public:
	TimeManager() {};
	~TimeManager() {};

public:

public:
    // 현재 시간을 int64_t 형태로 반환하는 함수
    static int64 GetCurrentTimeAsInt64()
    {
        // 현재 시간을 시간점(time point)으로 가져옴
        auto now = std::chrono::system_clock::now();
        // 시간점을 초 단위로 변환
        auto epoch = now.time_since_epoch();
        // 초를 밀리초로 변환하여 int64_t 형식으로 반환
        return std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
    }

    // 현재 시간을 string 형태로 반환하는 함수
    static std::string GetCurrentTimeAsString()
    {
        // 현재 시간을 시간점(time point)으로 가져옴
        auto now = std::chrono::system_clock::now();
        // 시간점을 시간 구조체로 변환
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        // 시간 구조체를 포맷된 문자열로 변환
        std::tm tm_struct;
        localtime_s(&tm_struct, &now_time); // C++11 이상에서 사용 가능

        std::ostringstream oss;
        oss << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }


    // BaseManager을(를) 통해 상속됨
    virtual void InitManager() override;

    virtual void ReleaseManager() override;

};

