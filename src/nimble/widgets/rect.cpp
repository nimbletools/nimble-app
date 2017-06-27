#include <nimble/common.h>
#include <nimble/widgets/rect.h>

#include <layout.h>
#include <nanovg.h>

na::RectWidget::RectWidget(Application* app, Widget* parent)
	: Widget(app, parent)
{
}

na::RectWidget::~RectWidget()
{
}

void na::RectWidget::DoLayout(lay_context* l, lay_id parent)
{
	lay_id id = BeginLayout(parent);
	lay_set_size_xy(l, id, m_size.x, m_size.y);

	Widget::DoLayout(l, id);
}

void na::RectWidget::Draw(NVGcontext* vg)
{
	if (m_color.a > 0.0f) {
		glm::ivec4 rect = GetLayout();

		nvgBeginPath(vg);
		nvgRect(vg, rect.x, rect.y, rect.z, rect.w);
		nvgFillColor(vg, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a));
		nvgFill(vg);
	}

	Widget::Draw(vg);
}

void na::RectWidget::SetSize(const glm::ivec2 &size)
{
	if (m_size != size) {
		InvalidateLayout();
	}
	m_size = size;
}

void na::RectWidget::SetColor(const glm::vec4 &color)
{
	if (m_color != color) {
		InvalidateRendering();
	}
	m_color = color;
}
