#pragma once

#include "ENPH.h"
#include "EventController.h"

namespace Engine
{
	class ENGINE_API WindowResizeEvent : public Event 
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:wWidth(width), wHeight(height) {};

		inline unsigned int GetWidth() { return wWidth; }
		inline unsigned int GetHeight() { return wHeight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: Width = " << wWidth << ", Heght = " << wHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int wWidth, wHeight;
	};

	class ENGINE_API WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {};

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {};
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {};
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {};
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}