#pragma once
/* Type define list */


/* 기본 자료형 재정의 */
#pragma region Types
//~ Unsigned base types from Unreal...

// 8-bit unsigned integer
typedef unsigned char 		uint8;

// 16-bit unsigned integer
typedef unsigned short int	uint16;

// 32-bit unsigned integer
typedef unsigned int		uint32;

// 64-bit unsigned integer
typedef unsigned long long	uint64;

//~ Signed base types.

// 8-bit signed integer
typedef	signed char			int8;

// 16-bit signed integer
typedef signed short int	int16;

// 32-bit signed integer
typedef signed int	 		int32;

// 64-bit signed integer
typedef signed long long	int64;

//~ Character types

// An ANSI character.
typedef char				ANSICHAR;

// A wide character.
typedef wchar_t				WIDECHAR;

// An 8-bit character type.
typedef uint8				CHAR8;

// A 16-bit character type.
typedef uint16				CHAR16;

// A 32-bit character type. 
typedef uint32				CHAR32;

// A switchable character.
typedef WIDECHAR			TCHAR;
#pragma endregion

/* shared_ptr 재정의 */
#pragma region UsingMacro
#define USING_SHARED_PTR(Cname)		using Cname##Ref = std::shared_ptr<class Cname>;

/* HyNetCore */


USING_SHARED_PTR(IOCP)
USING_SHARED_PTR(HySession)
USING_SHARED_PTR(SendBuffer)
USING_SHARED_PTR(RecvBuffer)
USING_SHARED_PTR(SendBufferChunk)
USING_SHARED_PTR(Job)
USING_SHARED_PTR(ScheduledJob)
USING_SHARED_PTR(JobScheduler)
USING_SHARED_PTR(JobQueue)


USING_SHARED_PTR(HyInstance)

USING_SHARED_PTR(JobManager)
USING_SHARED_PTR(ThreadManager)
USING_SHARED_PTR(SendBufferManager)

USING_SHARED_PTR(BaseManager)


/* Common */
USING_SHARED_PTR(User)
USING_SHARED_PTR(Room)
USING_SHARED_PTR(GameSession)
USING_SHARED_PTR(UserManager)
USING_SHARED_PTR(SessionManager)

/* Client */
USING_SHARED_PTR(HyClientInstance)


/* Server */
USING_SHARED_PTR(HyServerInstance)



#pragma endregion


// 함수 템플릿: std::unordered_map 또는 std::map에서 키가 존재하는지 검사
template <typename MapType, typename KeyType>
bool Contains(const MapType& map, const KeyType& key)
{
    return map.find(key) != map.end();
}
