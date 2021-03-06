#include <nimble/common.h>
#include <nimble/widget.h>
#include <nimble/widgetselector.h>
#include <nimble/app.h>

#include <layout.h>
#include <nanovg.h>

na::Widget::Widget(Application* app)
{
	m_app = app;
}

na::Widget::~Widget()
{
}

void na::Widget::InvalidateLayout()
{
	m_app->InvalidateLayout();
}

void na::Widget::InvalidateRendering()
{
	m_app->InvalidateRendering();
}

void na::Widget::BeginLayoutContainerFlags()
{
	assert(m_layID != 0);

	uint32_t flags = 0;

	if (m_layDir == WidgetDirection::Horizontal) {
		flags |= LAY_ROW;
	} else if (m_layDir == WidgetDirection::Vertical) {
		flags |= LAY_COLUMN;
	}

	if (m_layModel == WidgetModel::Layout) {
		flags |= LAY_LAYOUT;
	} else if (m_layModel == WidgetModel::Flex) {
		flags |= LAY_FLEX;
	}

	if (m_layWrap) {
		flags |= LAY_WRAP;
	} else {
		flags |= LAY_NOWRAP;
	}

	if (m_layJustify == WidgetJustify::Start) {
		flags |= LAY_START;
	} else if (m_layJustify == WidgetJustify::Middle) {
		flags |= LAY_MIDDLE;
	} else if (m_layJustify == WidgetJustify::End) {
		flags |= LAY_END;
	} else if (m_layJustify == WidgetJustify::Justify) {
		flags |= LAY_JUSTIFY;
	}

	lay_set_contain(m_app->m_layout, m_layID, flags);
}

void na::Widget::BeginLayoutBehaveFlags()
{
	assert(m_layID != 0);

	lay_set_behave(m_app->m_layout, m_layID, (uint32_t)m_layAnchor);
}

void na::Widget::BeginLayoutMargin()
{
	assert(m_layID != 0);

	int left = m_margin.m_left;
	int top = m_margin.m_top;
	int right = m_margin.m_right;
	int bottom = m_margin.m_bottom;

	lay_set_margins_ltrb(m_app->m_layout, m_layID, left, top, right, bottom);
}

lay_id na::Widget::BeginLayout(lay_id parent)
{
	m_layID = lay_item(m_app->m_layout);

	BeginLayoutContainerFlags();
	BeginLayoutBehaveFlags();
	BeginLayoutMargin();

	lay_insert(m_app->m_layout, parent, m_layID);

	return m_layID;
}

glm::ivec4 na::Widget::GetLayout()
{
	assert(m_layID != 0);

	lay_vec4 rect = lay_get_rect(m_app->m_layout, m_layID);
	return glm::ivec4(rect[0], rect[1], rect[2], rect[3]);
}

void na::Widget::Load(ContentNode &node)
{
	SetID(node.GetString("id", false, m_id));
	SetClass(node.GetString("class", false, m_class));

	SetVisible(node.GetBool("visible", false, m_visible));
	SetLayoutModel(node.GetBool("flex", false, m_layModel == WidgetModel::Flex) ? WidgetModel::Flex : WidgetModel::Layout);

	s2::string justify = node.GetString("justify", false);
	if (justify != "") {
		if (justify == "start") {
			SetLayoutJustify(WidgetJustify::Start);
		} else if (justify == "middle") {
			SetLayoutJustify(WidgetJustify::Middle);
		} else if (justify == "end") {
			SetLayoutJustify(WidgetJustify::End);
		} else if (justify == "justify") {
			SetLayoutJustify(WidgetJustify::Justify);
		} else {
			printf("Unknown justify %s\n", (const char*)justify);
		}
	}

	s2::string anchor = node.GetString("anchor", false);
	if (anchor != "") {
		s2::stringsplit parse = anchor.split(" ");
		int anchorFlags = AnchorNone;

		for (size_t i = 0; i < parse.len(); i++) {
			if (parse[i] == "none") { anchorFlags |= AnchorNone; }

			else if (parse[i] == "left") { anchorFlags |= AnchorLeft; }
			else if (parse[i] == "right") { anchorFlags |= AnchorRight; }
			else if (parse[i] == "top") { anchorFlags |= AnchorTop; }
			else if (parse[i] == "bottom") { anchorFlags |= AnchorBottom; }

			else if (parse[i] == "fillh") { anchorFlags |= AnchorFillH; }
			else if (parse[i] == "fillv") { anchorFlags |= AnchorFillV; }
			else if (parse[i] == "fill") { anchorFlags |= AnchorFill; }
			else {
				printf("Unknown anchor %s\n", (const char*)parse[i]);
			}
		}

		SetLayoutAnchor(anchorFlags);
	}

	SetLayoutWrapping(node.GetBool("wrapping", false, m_layWrap));

	SetMargin(node.GetBounds("margin", false, m_margin));

	s2::string cursor = node.GetString("cursor", false);
	if (cursor == "" || cursor == "arrow") {
		SetCursor(Cursor::Arrow);
	} else if (cursor == "ibeam") {
		SetCursor(Cursor::Ibeam);
	} else if (cursor == "crosshair") {
		SetCursor(Cursor::Crosshair);
	} else if (cursor == "hand") {
		SetCursor(Cursor::Hand);
	} else if (cursor == "hresize") {
		SetCursor(Cursor::HResize);
	} else if (cursor == "vresize") {
		SetCursor(Cursor::VResize);
	}
}

void na::Widget::DoLayout(lay_context* l, lay_id parent)
{
	for (Widget* child : m_children) {
		if (!child->m_visible) {
			continue;
		}
		child->DoLayout(l, parent);
	}
}

void na::Widget::Draw(NVGcontext* vg)
{
	for (Widget* child : m_children) {
		if (!child->m_visible) {
			continue;
		}
		child->Draw(vg);
	}
}

bool na::Widget::Contains(const glm::ivec2 &absPoint)
{
	glm::ivec4 rect = GetLayout();
	return
	  (absPoint.x >= rect.x && absPoint.x < rect.x + rect.z) &&
	  (absPoint.y >= rect.y && absPoint.y < rect.y + rect.w);
}

glm::ivec2 na::Widget::ToRelativePoint(const glm::ivec2 &absPoint)
{
	glm::ivec4 rect = GetLayout();
	return glm::ivec2(
		absPoint.x - rect.x,
		absPoint.y - rect.y
	);
}

glm::ivec2 na::Widget::ToAbsolutePoint(const glm::ivec2 &point)
{
	glm::ivec4 rect = GetLayout();
	return glm::ivec2(
		point.x + rect.x,
		point.y + rect.y
	);
}

void na::Widget::OnMouseEnter()
{
	m_hovering = true;
}

void na::Widget::OnMouseLeave()
{
	m_hovering = false;
}

void na::Widget::OnMouseDown(int button, const glm::ivec2 &point)
{
}

void na::Widget::OnMouseMove(const glm::ivec2 &point)
{
}

void na::Widget::OnMouseUp(int button, const glm::ivec2 &point)
{
}

bool na::Widget::HasFocus()
{
	return m_app->GetFocusWidget() == this;
}

bool na::Widget::CanHaveFocus()
{
	return false;
}

void na::Widget::SetFocus()
{
	m_app->SetFocusWidget(this);
}

void na::Widget::OnFocus()
{
}

void na::Widget::OnFocusLost()
{
}

void na::Widget::OnKeyDown(int key, int scancode, int mods)
{
}

void na::Widget::OnKeyPress(int key, int scancode, int mods)
{
}

void na::Widget::OnKeyUp(int key, int scancode, int mods)
{
}

void na::Widget::OnChar(unsigned int ch, int mods)
{
}

void na::Widget::AddChild(Widget* child)
{
	assert(child->m_parent == nullptr);

	child->m_parent = this;
	m_children.add(child);

	InvalidateLayout();
}

na::Widget* na::Widget::SelectorOne(const s2::string &query)
{
	WidgetSelectorNode node;
	node.Parse(query);
	return node.MatchOne(this);
}

void na::Widget::Selector(const s2::string &query, s2::list<Widget*> &out)
{
	WidgetSelectorNode node;
	node.Parse(query);
	node.Match(this, out);
}

void na::Widget::SetTagName(const s2::string &name)
{
	m_tagname = name;
}

void na::Widget::SetID(const s2::string &id)
{
	if (m_id != id) {
		//TODO: Invalidate style
	}
	m_id = id;
}

void na::Widget::SetClass(const s2::string &name)
{
	if (m_class != name) {
		//TODO: Invalidate style
	}
	m_class = name;
}

void na::Widget::SetVisible(bool visible)
{
	if (m_visible != visible) {
		InvalidateLayout();
	}
	m_visible = visible;
}

void na::Widget::SetCursor(Cursor cursor)
{
	if (m_cursor != cursor) {
		m_app->InvalidateCursor();
	}
	m_cursor = cursor;
}

void na::Widget::SetLayoutDirection(WidgetDirection dir)
{
	if (m_layDir != dir) {
		InvalidateLayout();
	}
	m_layDir = dir;
}

void na::Widget::SetLayoutModel(WidgetModel model)
{
	if (m_layModel != model) {
		InvalidateLayout();
	}
	m_layModel = model;
}

void na::Widget::SetLayoutJustify(WidgetJustify justify)
{
	if (m_layJustify != justify) {
		InvalidateLayout();
	}
	m_layJustify = justify;
}

void na::Widget::SetLayoutAnchor(WidgetAnchor anchor)
{
	if (m_layAnchor != anchor) {
		InvalidateLayout();
	}
	m_layAnchor = anchor;
}

void na::Widget::SetLayoutWrapping(bool wrap)
{
	if (m_layWrap != wrap) {
		InvalidateLayout();
	}
	m_layWrap = wrap;
}

void na::Widget::SetMargin(const Bounds &margin)
{
	if (m_margin != margin) {
		InvalidateLayout();
	}
	m_margin = margin;
}
