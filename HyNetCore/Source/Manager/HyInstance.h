#pragma once

/*

	언리얼 gameinstance처럼
	하나의 인스턴스만 생성하여 전역적으로 관리
	manager 등
*/

extern HyInstanceRef Ginstance;

class HyInstance : public std::enable_shared_from_this<HyInstance>
{
public:
	HyInstance(E_CORE_CONNECT Incore_connect);
	virtual ~HyInstance();

public:
	virtual void InitHyInstance() abstract;
	virtual void ReleaseInstance() abstract;

protected:
	virtual void InitGInstance();

	virtual void InitProtocol() abstract;
	virtual void InitManager() abstract;

	virtual void ReleaseGInstance();
	virtual void ReleaseManager();


public:
	template<typename T>
	std::shared_ptr<T> GetManager()
	{
		// TODO 타입 체크
		//std::static_assert(std::is_base_of<BaseManager, T>::value, "T must be derived from BaseManager");
		//ASSERT_CRASH(std::is_base_of<BaseManager, T>::value);

		// TOOD 모든 매니저 순회하면서 dynamic ptra cast 하는거라 인덱스 연산으로 수정 필요
		for (const auto& manager : managers)
		{
			if (auto derived = std::dynamic_pointer_cast<T>(manager))
			{
				return derived;
			}
		}

		return nullptr;
	}

	bool IsServerConnect() { return (core_connect == E_CORE_CONNECT::E_CONNECT_SERVER); }

public:
	GETTER(IOCPRef, IocpRef);
	SETTER(IOCPRef, IocpRef);

	GETTER(std::shared_ptr<class ISessionManager>, isessionMgr);

	GETTER(JobManagerRef, jobMgr);
	GETTER(ThreadManagerRef, threadMgr);
	GETTER(SendBufferManagerRef, sendBufferMgr);

protected:
	std::vector<BaseManagerRef> managers;
	std::shared_ptr<class ISessionManager> isessionMgr;

	JobManagerRef jobMgr;
	ThreadManagerRef threadMgr;
	SendBufferManagerRef sendBufferMgr;

	E_CORE_CONNECT core_connect;
	IOCPRef IocpRef;

};
