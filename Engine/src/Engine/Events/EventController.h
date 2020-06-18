#pragma once

#include "ENPH.h"
#include "Engine/Core.h"

namespace Engine 
{
	//Currently it stops the moment an event is triggered
	//A better way to implement it is by using a buffer
	//TODO: Implement it

	enum class EventType
	{
		Undefinded = 0,
		WindowClosed, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		Undefined = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }
		inline bool IsHandled() const { return eHandled; }
	protected:
		bool eHandled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) 
			:dEvent(event)
		{
		}
		
		template<typename T>
		bool Dispatch(EventFn<T> func) 
		{
			if (dEvent.GetEventType() == T::GetStaticType()) 
			{
				dEvent.eHandled = func(*(T*)&dEvent);
				return true;
			}
			return false;
		}

	private:
		Event& dEvent;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}