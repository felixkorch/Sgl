#pragma once
#include "Sgl/Events/Event.h"

namespace sgl
{
	class MouseEvent : public Event {
	};

	class CursorEvent : public MouseEvent {
	protected:
		double xPos, yPos;
	public:
		CursorEvent(double xPos, double yPos)
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
			ss << "CursorEvent: (" << xPos << ", " << yPos << ")";
			return ss.str();
		}

		const EventType GetEventType() const override
		{
			return EventType::CursorMoved;
		}

		static EventType GetStaticType() { return EventType::CursorMoved; }
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