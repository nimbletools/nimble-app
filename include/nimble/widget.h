#pragma once

#include "common.h"

typedef uint32_t lay_id;

struct lay_context;
struct NVGcontext;

namespace na
{
	class Application;

	class Widget
	{
	private:
		Application* m_app;
		Widget* m_parent;

		bool m_visible = true;

		s2::list<Widget*> m_children;

	private:
		lay_id m_layID = 0;

	protected:
		Widget(Application* app, Widget* parent);
		virtual ~Widget();

		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual lay_id BeginLayout(lay_id parent);
		virtual glm::ivec4 GetLayout();

	public:
		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		inline bool IsVisible() { return m_visible; }
		virtual void SetVisible(bool visible);
	};
}
