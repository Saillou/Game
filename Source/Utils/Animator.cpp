#include "Animator.hpp"

Animator::Tweet::Tweet(const float duration_sec, const Type type):
	m_duration(duration_sec), 
	m_type(type)
{
	m_time.tic();
}
