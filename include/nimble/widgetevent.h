#pragma once

#include "common.h"

namespace na
{
	class Widget;

	class WidgetEvent
	{
	public:
		WidgetEvent();
		virtual ~WidgetEvent();
	};

	typedef s2::func<void(Widget*, WidgetEvent)> EventHandler;

	class EventList : public s2::list<EventHandler>
	{
	public:
		void operator ()(Widget* sender);
		void operator ()(Widget* sender, WidgetEvent e);
	};
}
