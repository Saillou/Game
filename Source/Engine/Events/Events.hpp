#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>

#include "Common.hpp"

class Event {
protected:
	// List possibilities
	enum class _Type : int {
		Undefined = 0,
		KeyPressed,
	};

	// Abstract base event
	struct _Base {
		_Base(_Type id = _Type::Undefined) : _id(id) {
			// ..
		}
		virtual ~_Base() = default;

		const _Type id() const { 
			return _id;
		};

	private:
		_Type _id;
	};

public:
	// [Emitter]
	template <typename T> inline
		static void Emit(const T& event);

	// [Receiver]
	class Subscriber {
		friend Event;

	public:
		Subscriber();
		virtual ~Subscriber();

	protected:
		template <class _subscriber, typename _message> inline
			void _subscribe(void(_subscriber::*callback)(const _message&));

	private:
		// Note: 
		//	these are temporary callbacks used to crush the _message type to _Base (inherited) type,
		//  the final callback provided by the subscriber is encapsulated in the crushy callback.
		typedef std::function<void(const Event::_Base*)> _crushyCallback;
		std::unordered_map<_Type, std::vector<_crushyCallback>> _callbacks;
	};

	// Define events available
	// -- Keyboard --
	struct KeyPressed : public _Base {
		explicit KeyPressed(int key = -1);
		int key;
	};

private:
	static std::unordered_set<Subscriber*> _allSubscribers;
};

// Template Implementation
template<typename T>
inline void Event::Emit(const T& event)
{
	static_assert(std::is_base_of<Event::_Base, T>(), "Can't emit non inherited BaseEvent.");

	for (Subscriber* subscriber : _allSubscribers) {
		for (const Subscriber::_crushyCallback& callback : subscriber->_callbacks[event.id()]) {
			callback(static_cast<const Event::_Base*>(&event));
		}
	}
}

template<class _subscriber, typename _message>
inline void Event::Subscriber::_subscribe(void(_subscriber::*finalCallback)(const _message&))
{
	static_assert(std::is_base_of<Event::_Base, Event::KeyPressed>(), "Can't subscribe to non inherited BaseEvent.");

	// Memorize id from type
	static const _Type type = _message{}.id();

	// Encapsulate the final callback
	const _crushyCallback crushy = [=](const Event::_Base* msg) -> void 
	{
		std::invoke(finalCallback, static_cast<_subscriber*>(this), *static_cast<const _message*>(msg));
	};

	// Add to callbacks
	_callbacks[type].push_back(crushy);
}
