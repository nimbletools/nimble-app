#include <nimble/common.h>
#include <nimble/widgetevent.h>

na::WidgetEvent::WidgetEvent()
{
}

na::WidgetEvent::~WidgetEvent()
{
}

void na::EventList::operator ()(Widget* sender)
{
	operator ()(sender, WidgetEvent());
}

void na::EventList::operator ()(Widget* sender, WidgetEvent e)
{
	for (auto &func : *this) {
		func(sender, e);
	}
}
