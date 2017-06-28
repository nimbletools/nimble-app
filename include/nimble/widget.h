#pragma once

#include "common.h"
#include "bounds.h"

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

	enum WidgetAnchor
	{
		AnchorNone = 0,

		AnchorLeft = 0x020,
		AnchorRight = 0x080,
		AnchorTop = 0x040,
		AnchorBottom = 0x100,

		AnchorFillH = AnchorLeft | AnchorRight,
		AnchorFillV = AnchorTop | AnchorBottom,
		AnchorFill = AnchorLeft | AnchorRight | AnchorTop | AnchorBottom,
	};

	class Widget
	{
	private:
		Application* m_app;
		Widget* m_parent = nullptr;

		bool m_visible = true;

		s2::list<Widget*> m_children;

		lay_id m_layID = 0;
		WidgetDirection m_layDir = WidgetDirection::None;
		WidgetModel m_layModel = WidgetModel::Layout;
		WidgetJustify m_layJustify = WidgetJustify::Start;
		WidgetAnchor m_layAnchor = AnchorNone;
		bool m_layWrap = false;

		Bounds m_margin;

		bool m_hovering = false;

	protected:
		Widget(Application* app);
		virtual ~Widget();

		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual void BeginLayoutContainerFlags();
		virtual void BeginLayoutBehaveFlags();
		virtual void BeginLayoutMargin();
		virtual lay_id BeginLayout(lay_id parent);
		virtual glm::ivec4 GetLayout();

	public:
		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		virtual bool Contains(const glm::ivec2 &absPoint);

		virtual void OnMouseEnter();
		virtual void OnMouseLeave();
		virtual void OnMouseDown(int button);
		virtual void OnMouseUp(int button);

		inline const s2::list<Widget*> &GetChildren() { return m_children; }
		virtual void AddChild(Widget* child);

		inline bool IsHovering() { return m_hovering; }

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
		inline void SetLayoutAnchor(int anchor) { SetLayoutAnchor((WidgetAnchor)anchor); }

		inline bool IsLayoutWrapping() { return m_layWrap; }
		virtual void SetLayoutWrapping(bool wrap);

		inline Bounds GetMargin() { return m_margin; }
		virtual void SetMargin(const Bounds &margin);
	};
}
