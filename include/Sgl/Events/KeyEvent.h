#pragma once
#include "Sgl/Events/Event.h"

namespace sgl
{
	class KeyEvent : public Event {
	protected:
		int keyCode;
	public:
		KeyEvent(int code, int repeatCount = 0)
			: keyCode(code) {}

		int GetKeyCode()
		{
			return keyCode;
		}
	};

	class KeyPressedEvent : public KeyEvent {
	private:
		int repeatCount;
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), repeatCount(repeatCount) {}

		int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::KeyPressed;
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
	};

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << keyCode;
            return ss.str();
        }

        const EventType GetEventType() const override
        {
            return EventType::KeyTyped;
        }

        static EventType GetStaticType() { return EventType::KeyTyped; }
    };

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::KeyReleased;
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
	};
}