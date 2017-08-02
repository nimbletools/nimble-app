#pragma once

#include "../common.h"
#include "../widget.h"

namespace na
{
	class Application;

	class PageWidget : public Widget
	{
	public:
		PageWidget(Application* app, const s2::string &layoutFnm);
		virtual ~PageWidget();

		virtual void DoLayout(lay_context* l, lay_id parent);

		virtual void LoadLayout(const s2::string &filename);
	};
}
