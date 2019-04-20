#pragma once
#include "Sgl/Events/Event.h"

namespace sgl
{
	class MouseEvent : public Event {
	};

	class MouseMovedEvent : public MouseEvent {
	protected:
		double xPos, yPos;
	public:
		MouseMovedEvent(double xPos, double yPos)
			: xPos(xPos), yPos(yPos) {}
		
		double GetXPos()
		{
			return xPos;
		}

		double GetYPos()
		{
			return yPos;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Position: (" << xPos << ", " << yPos << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::MouseMoved;
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
	};

	class MouseButtonPressed : public MouseEvent {
	protected:
		int button;
	public:
		MouseButtonPressed(int button)
			: button(button) {}

		int GetButton()
		{
			return button;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: (" << button << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::MouseButtonPressed;
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
	};

	class MouseButtonReleased: public MouseEvent {
	protected:
		int button;
	public:
		MouseButtonReleased(int button)
			: button(button) {}

		int GetButton()
		{
			return button;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: (" << button << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::MouseButtonReleased;
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
	};
}