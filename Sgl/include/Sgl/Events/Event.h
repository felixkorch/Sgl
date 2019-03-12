#pragma once
#include <sstream>
#include <functional>

namespace sgl
{
	enum class EventType {
		WindowClose, KeyPressed, KeyReleased, KeyRepeat, MouseMoved, MouseButtonPressed, MouseButtonReleased,
		JoystickButtonPressed, JoystickButtonReleased, DropCallbackEvent
	};

	class Event {
	public:
		bool handled = false;
		const virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const = 0;

	};

	class EventDispatcher {
	private:
		Event& event;

		template<class T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			: event(e) {}

		template<class T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetEventType() == T::GetStaticType()) {
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}
	};

	/*std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}*/
}