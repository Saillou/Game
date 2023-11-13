#pragma once

#include <chrono>

class Timer {
	using _time_point = std::chrono::time_point<std::chrono::system_clock>;

	// Base
	struct _time_policy {
		template <typename ReturnT> inline
			static ReturnT Get(const _time_point&) = 0;
	};

public:
	// Policies
	struct millisecond : public _time_policy {
		template <typename ReturnT> inline
			static ReturnT Get(const _time_point& tp)
		{
			return static_cast<ReturnT>(
				std::chrono::time_point_cast<std::chrono::milliseconds>(tp).time_since_epoch().count()
			);
		}
	};

	// Get time
	template <typename TimePolicy> inline
		static int GetCurrentTime() 
	{
		static_assert(std::is_base_of<_time_policy, TimePolicy>(), "Bad time policy");

		return TimePolicy::Get<int>(std::chrono::system_clock::now());
	}
};