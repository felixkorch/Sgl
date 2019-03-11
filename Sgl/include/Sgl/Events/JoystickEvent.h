#pragma once
#include "Sgl/Events/Event.h"

namespace sgl
{
	class JoystickEvent : public Event {
	};

	class JoystickButtonPressed : public JoystickEvent {
	protected:
		int button;
	public:
		JoystickButtonPressed(int button)
			: button(button) {}

		int GetButton()
		{
			return button;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoystickButtonPressed: (" << button << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::JoystickButtonPressed;
		}

		static EventType GetStaticType() { return EventType::JoystickButtonPressed; }
	};

	class JoystickButtonReleased : public JoystickEvent {
	protected:
		int button;
	public:
		JoystickButtonReleased(int button)
			: button(button) {}

		int GetButton()
		{
			return button;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoystickButtonReleased: (" << button << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::JoystickButtonReleased;
		}

		static EventType GetStaticType() { return EventType::JoystickButtonReleased; }
	};
}