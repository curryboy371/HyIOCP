#pragma once
#include <random>

class HyUtils
{
public:
	static bool IsInvaildID(const int64& inID)
	{
		if (inID <= 0)
		{
			return false;
		}

		return true;
	}


	template<typename T>
	static T GetRandom(T min, T max)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> distribution(min, max);
			return distribution(generator);
		}
		else
		{
			std::uniform_real_distribution<T> distribution(min, max);
			return distribution(generator);
		}
	}
};

