#pragma once
#include "dmpch.h"

#include "Dream/Core.h"

namespace Dream {

	// Events in Dream are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with instantly.
	// For the future, it might be better to buffer events in an event bus and
	// process them during an "event" part of the update stage.

	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory //created a bit field 
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class DREAM_API Event
	{
		friend class EventDispatcher;
	public:

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	
		
	};

	// Create an event dispatcher instance to easily dispatch events based on their type.
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// Call dispatch with different Event functions that has a bool return type and takes in a type T reference.
		// In this case T can be any event type like WindowResizeEvent for example.
		// If the event that you are trying to dispatch matches the type of this function passed.
		// It will call the function with that event.
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator <<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}