#include <nimble/common.h>
#include <nimble/widget.h>
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

void na::Widget::OnMouseEnter()
{
	m_hovering = true;
}

void na::Widget::OnMouseLeave()
{
	m_hovering = false;
}

void na::Widget::OnMouseDown(int button)
{
}

void na::Widget::OnMouseUp(int button)
{
}

void na::Widget::AddChild(Widget* child)
{
	assert(child->m_parent == nullptr);

	child->m_parent = this;
	m_children.add(child);

	InvalidateLayout();
}

void na::Widget::SetVisible(bool visible)
{
	if (m_visible != visible) {
		InvalidateLayout();
	}
	m_visible = visible;
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
