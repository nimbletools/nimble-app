#include <nimble/common.h>
#include <nimble/widget.h>
#include <nimble/app.h>

#include <layout.h>
#include <nanovg.h>

na::Widget::Widget(Application* app, Widget* parent)
{
	m_app = app;
	m_parent = parent;
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

lay_id na::Widget::BeginLayout(lay_id parent)
{
	m_layID = lay_item(m_app->m_layout);
	lay_insert(m_app->m_layout, parent, m_layID);
	return m_layID;
}

glm::ivec4 na::Widget::GetLayout()
{
	assert(m_layID != 0);
	if (m_layID == 0) {
		return glm::ivec4();
	}
	lay_vec4 rect = lay_get_rect(m_app->m_layout, m_layID);
	return glm::ivec4(rect[0], rect[1], rect[2], rect[3]);
}

void na::Widget::DoLayout(lay_context* l, lay_id parent)
{
	for (Widget* child : m_children) {
		child->DoLayout(l, parent);
	}
}

void na::Widget::Draw(NVGcontext* vg)
{
	for (Widget* child : m_children) {
		child->Draw(vg);
	}
}

void na::Widget::SetVisible(bool visible)
{
	if (m_visible != visible) {
		InvalidateLayout();
	}
	m_visible = visible;
}
