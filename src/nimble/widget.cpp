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
