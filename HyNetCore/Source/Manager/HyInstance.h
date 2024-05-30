#pragma once

/*

	언리얼 gameinstance처럼
	하나의 인스턴스만 생성하여 전역적으로 관리
	manager 등
*/

//extern class HyServerInstance* Ginstance;

extern JobManagerRef GjobMgr;
extern ThreadManagerRef GthreadMgr;
extern SendBufferManagerRef GsendBufferMgr;

class HyInstance : public std::enable_shared_from_this<HyInstance>
{
public:
	HyInstance();
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
		// TODO 
		//std::static_assert(std::is_base_of<BaseManager, T>::value, "T must be derived from BaseManager");
		//ASSERT_CRASH(std::is_base_of<BaseManager, T>::value);

		for (const auto& manager : managers)
		{
			if (auto derived = std::dynamic_pointer_cast<T>(manager))
			{
				return derived;
			}
		}

		return nullptr;
	}

protected:
	std::vector<BaseManagerRef> managers;
};

