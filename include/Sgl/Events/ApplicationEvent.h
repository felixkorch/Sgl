#pragma once
#include "Sgl/Events/Event.h"
#include <vector>

namespace sgl
{
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		const EventType GetEventType() const override
		{
			return EventType::WindowClose;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent occured!";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::WindowClose; }
	};

	class WindowResizedEvent : public Event {
	private:
		int width, height;
	public:
		WindowResizedEvent(int width, int height)
			: width(width), height(height) {}

		const EventType GetEventType() const override
		{
			return EventType::WindowResizedEvent;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent occured!";
			return ss.str();
		}

		int GetWidth()
		{
			return width;
		}

		int GetHeight()
		{
			return height;
		}

		static EventType GetStaticType() { return EventType::WindowResizedEvent; }
	};

	class DropEvent : public Event {
	private:
		std::vector<std::string> paths;
	public:
		DropEvent(int count, const char** _paths)
		{
			for (int i = 0; i < count; i++) {
				const char* temp = _paths[i];
				paths.emplace_back(std::string(temp));
			}
		}

		const EventType GetEventType() const override
		{
			return EventType::DropEvent;
		}

		std::vector<std::string> GetPaths()
		{
			return paths;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Files Dropped:";
			for (const auto& p : paths)
				ss << std::endl << p;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::DropEvent; }
	};
}