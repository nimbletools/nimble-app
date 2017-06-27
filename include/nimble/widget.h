#pragma once

#include "common.h"

typedef uint32_t lay_id;

struct lay_context;
struct NVGcontext;

namespace na
{
	class Application;

	enum class WidgetDirection
	{
		None,
		Horizontal,
		Vertical,
	};

	enum class WidgetModel
	{
		Layout,
		Flex,
	};

	enum class WidgetJustify
	{
		Start,
		Middle,
		End,
		Justify,
	};

	enum class WidgetAnchor
	{
		None = 0,

		Left = 0x020,
		Right = 0x080,
		Top = 0x040,
		Bottom = 0x100,

		FillH = Left | Right,
		FillV = Top | Bottom,
		Fill = Left | Right | Top | Bottom,
	};

	class Widget
	{
	private:
		Application* m_app;
		Widget* m_parent;

		bool m_visible = true;

		s2::list<Widget*> m_children;

		lay_id m_layID = 0;
		WidgetDirection m_layDir = WidgetDirection::None;
		WidgetModel m_layModel = WidgetModel::Layout;
		WidgetJustify m_layJustify = WidgetJustify::Start;
		WidgetAnchor m_layAnchor = WidgetAnchor::None;
		bool m_layWrap = false;

	protected:
		Widget(Application* app, Widget* parent);
		virtual ~Widget();

		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual void SetContainerFlags();
		virtual void SetBehaveFlags();
		virtual lay_id BeginLayout(lay_id parent);
		virtual glm::ivec4 GetLayout();

	public:
		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		inline bool IsVisible() { return m_visible; }
		virtual void SetVisible(bool visible);

		inline WidgetDirection GetLayoutDirection() { return m_layDir; }
		virtual void SetLayoutDirection(WidgetDirection dir);

		inline WidgetModel GetLayoutModel() { return m_layModel; }
		virtual void SetLayoutModel(WidgetModel model);

		inline WidgetJustify GetLayoutJustify() { return m_layJustify; }
		virtual void SetLayoutJustify(WidgetJustify justify);

		inline WidgetAnchor GetLayoutAnchor() { return m_layAnchor; }
		virtual void SetLayoutAnchor(WidgetAnchor anchor);

		inline bool IsLayoutWrapping() { return m_layWrap; }
		virtual void SetLayoutWrapping(bool wrap);
	};
}
