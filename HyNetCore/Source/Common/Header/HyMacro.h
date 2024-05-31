#pragma once


#pragma region Value
/* Macro Define */
#define RECV_BURRER_SIZE 0x10000
#define MAX_RECV_SIZE 4096


#define INVALID_INDEX		 -1
#define INVALID_UID			 0

#pragma endregion





#pragma region Log

#define DEF_LOG				std::cout << __FUNCTION__ << std::endl


#define DEF_LOGG			LogGuard logGuard(__FUNCTION__)
#define DEF_ENDLOGG			logGuard.EndLogGuard();

struct LogGuard
{
	LogGuard(const char* InfunctionName)
	{
		strncpy_s(this->functionName, InfunctionName, _TRUNCATE);
		functionName[sizeof(functionName) - 1] = '\0'; // Null-terminate to avoid overflow

		std::cout << "[Start] " << functionName << std::endl;
	}

	void EndLogGuard()
	{
		std::cout << "[End] " << functionName << std::endl;
	}

	~LogGuard()
	{
		//std::cout << "[End]" << functionName << std::endl;
	}

	char functionName[256];
};

#define WSALOG(error) L"WSA_ERROR-" + std::to_wstring(error)

inline std::wstring GetLogInfo(const char* function, int line, const std::wstring& txt)
{
	std::wstring wFunction = std::wstring(function, function + strlen(function));
	return wFunction + L"(" + std::to_wstring(line) + L"): " + txt;
}

// 매크로 정의
#define LOG_INFO(txt) GetLogInfo(__FUNCTION__, __LINE__, txt).c_str()

#pragma endregion


#pragma region GetterSetter

#define GETTER(type, name) \
public: \
    const type& Get_##name##Ref() const { return name; } \
	type Get_##name() const { return name; } \
private:

#define SETTER(type, name) \
public: \
    void Set_##name(const type& value) { name = value; } \
private:


#pragma endregion

#pragma region Space

#define BEGIN_NS(name) namespace ##nameCore {
#define END_NS }

#define BEGIN_SERVER namespace Server {
#define END_SERVER }

#define BEGIN_CLIENT namespace Client {
#define END_CLIENT }

#define BEGIN_CORE namespace NetCore {
#define END_CORE }

#define USING_CORE using namespace NetCore;
#define USING_SERVER using namespace Server;
#define USING_CLIENT using namespace Client;

#pragma endregion


#pragma region LockGuard

#define DEF_MUTEX																	\
						protected:													\
							std::recursive_mutex mLock;								\
						public:														\
							std::recursive_mutex& GetLock() { return mLock; }		\
						private:


#define USE_MULOCK		LockGuard lockGuard(GetLock())

#pragma endregion


/* assert crash define */
#pragma region Macro_Crash

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}



#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}			

#pragma endregion


