#pragma once

#include "../common.h"
#include "rect.h"

namespace na
{
	class ButtonWidget : public RectWidget
	{
	public:
		ButtonWidget(Application* app);
		virtual ~ButtonWidget();

		virtual void OnMouseEnter();
		virtual void OnMouseLeave();
		virtual void OnMouseDown(int button);
		virtual void OnMouseUp(int button);
	};
}
