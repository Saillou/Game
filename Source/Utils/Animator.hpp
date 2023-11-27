#pragma once

#include "Timer.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <iostream>

struct Animator {
	struct Tweet {
		enum class Type {
			Linear, Quadratic
		};

		Tweet(const float duration_sec, const Type type = Type::Linear);

		template <typename T> inline
			T update(const T& start, const T& end);

	private:
		float _get_rel_time() {
			return glm::clamp((m_time.elapsed<Timer::millisecond>() / 1000.0f) / m_duration, 0.0f, 1.0f);
		}

		Timer::Chronometre m_time;
		const float m_duration;
		const Type m_type;
	};

	typedef std::unique_ptr<Tweet> uTweet;
};

template<typename T>
inline T Animator::Tweet::update(const T& start, const T& end) 
{
	if (start == end)
		return end;

	const float a = _get_rel_time();

	switch (m_type) {
		case Type::Linear:		return end * a     + start * (1.0f - a);
		case Type::Quadratic:	return end * (a*a) + start * (1.0f - a*a);
	}
	return end;
}

template <>
inline std::string Animator::Tweet::update(const std::string& start, const std::string& end)
{
	return end;
}
