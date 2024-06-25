#pragma once


#pragma region Value
/* Macro Define */
#define RECV_BURRER_SIZE 0x10000
#define MAX_RECV_SIZE 4096

#define MAX_SERVER_SESSION 50
#define CLIENT_SESSION 50

#define INVALID_INDEX		 -1
#define INVALID_UID			 0

#define DETAIL_LOG			1

#pragma endregion



#pragma region Log

#define STRINGIFY(x) #x

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

template<typename... Args>
void log_message(const std::string& level, const char* file, const char* function, int line, const std::string& fmt, Args... args) 
{
	printf_s(("[%s][%s::%s(%d)] " + fmt + "\n").c_str(), level.c_str(), file, function, line, args...);
}

// 로그 메시지 함수 - 문자열만 출력
void log_message_string(const std::string& level, const char* message);


#ifdef DETAIL_LOG
	#define LOG_E(msg) log_message_string("LOG", msg)
	#define LOG_I log_message("LOG", __FILENAME__, __func__, __LINE__, "")
	#define LOG_V(Fmt, ...) log_message("LOG", __FILENAME__, __func__, __LINE__, Fmt, ##__VA_ARGS__)
	#define WAR_V(Fmt, ...) log_message("WAR", __FILENAME__, __func__, __LINE__, Fmt, ##__VA_ARGS__)
	#define ERR_V(Fmt, ...) log_message("ERR", __FILENAME__, __func__, __LINE__, Fmt, ##__VA_ARGS__)

	#define LOG_FUNC			LOG_E(__FUNCTION__)
	#define LOG_GUARD			LogGuard logGuard(__FUNCTION__)
	#define END_LOGGUARD		logGuard.EndLogGuard();

	struct LogGuard
	{
		LogGuard(const char* InfunctionName)
		{
			strncpy_s(this->functionName, InfunctionName, _TRUNCATE);
			functionName[sizeof(functionName) - 1] = '\0'; // Null-terminate to avoid overflow

			// 로그 메시지를 작성
			std::string strLog = "[Start] " + std::string(functionName);
			LOG_E(strLog.c_str());
		}

		void EndLogGuard()
		{
			std::string strLog = "[EndLogGuard] " + std::string(functionName);
			LOG_E(strLog.c_str());
			bPrintEnd = false;
		}

		~LogGuard()
		{
			if (bPrintEnd)
			{
				std::string strLog = "[End] " + std::string(functionName);
				LOG_E(strLog.c_str());
			}

		}

		char functionName[256];
		bool bPrintEnd = true;
	};




#else
	#define LOG_E(msg) 
	#define LOG_I 
	#define LOG_V(Fmt, ...) 
	#define WAR_V(Fmt, ...) 
	#define ERR_V(Fmt, ...) 

	#define LOG_FUNC			
	#define LOG_GUARD			
	#define END_LOGGUARD		
#endif

inline std::wstring GetLogInfo(const char* function, int line, const std::wstring& txt)
{
	std::wstring wFunction = std::wstring(function, function + strlen(function));
	return wFunction + L"(" + std::to_wstring(line) + L"): " + txt;
}

// 매크로 정의
#define WSALOG(error) L"WSA_ERROR-" + std::to_wstring(error)
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


