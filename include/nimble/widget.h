#pragma once

#include "common.h"
#include "contentnode.h"
#include "widgetevent.h"
#include "utils/bounds.h"

typedef uint32_t lay_id;

struct lay_context;
struct NVGcontext;

namespace na
{
	class Application;
	class Widget;

	typedef s2::func<Widget*()> WidgetFactory;

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

	enum class Cursor
	{
		Arrow,
		Ibeam,
		Crosshair,
		Hand,
		HResize,
		VResize,
	};

	class Widget
	{
		//TODO: Add ref count

	protected:
		Application* m_app;
		Widget* m_parent = nullptr;

	private:
		s2::string m_tagname;
		s2::string m_id;
		s2::string m_class;
		bool m_visible = true;

		Cursor m_cursor = Cursor::Arrow;

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
		virtual void Load(ContentNode &node);

		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		virtual bool Contains(const glm::ivec2 &absPoint);
		virtual glm::ivec2 ToRelativePoint(const glm::ivec2 &absPoint);
		virtual glm::ivec2 ToAbsolutePoint(const glm::ivec2 &point);

		virtual void OnMouseEnter();
		virtual void OnMouseLeave();
		virtual void OnMouseDown(int button, const glm::ivec2 &point);
		virtual void OnMouseMove(const glm::ivec2 &point);
		virtual void OnMouseUp(int button, const glm::ivec2 &point);

		virtual bool HasFocus();
		virtual bool CanHaveFocus();
		virtual void SetFocus();
		virtual void OnFocus();
		virtual void OnFocusLost();

		virtual void OnKeyDown(int key, int scancode, int mods);
		virtual void OnKeyPress(int key, int scancode, int mods);
		virtual void OnKeyUp(int key, int scancode, int mods);
		virtual void OnChar(unsigned int ch, int mods);

		inline const s2::list<Widget*> &GetChildren() { return m_children; }
		virtual void AddChild(Widget* child);

		virtual Widget* SelectorOne(const s2::string &query);
		template<typename T>
		inline T* Selector(const s2::string &query) { return (T*)SelectorOne(query); }
		virtual void Selector(const s2::string &query, s2::list<Widget*> &out);

		inline bool IsHovering() { return m_hovering; }

		inline s2::string GetTagName() { return m_tagname; }
		virtual void SetTagName(const s2::string &name);

		inline s2::string GetID() { return m_id; }
		virtual void SetID(const s2::string &id);

		inline s2::string GetClass() { return m_class; }
		virtual void SetClass(const s2::string &name);

		inline bool IsVisible() { return m_visible; }
		virtual void SetVisible(bool visible);

		inline Cursor GetCursor() { return m_cursor; }
		virtual void SetCursor(Cursor cursor);

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
