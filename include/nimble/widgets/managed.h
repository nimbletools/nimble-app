#pragma once

#include "../common.h"
#include "../widget.h"

#include "../managed/managedcode.h"

namespace na
{
	class ManagedWidget : public Widget
	{
	private:
		MonoObject* m_object;

	public:
		ManagedWidget(Application* app, MonoObject* obj);
		virtual ~ManagedWidget();
	};
}
