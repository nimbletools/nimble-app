#include <nimble/common.h>
#include <nimble/widgets/rect.h>

#include <layout.h>
#include <nanovg.h>

na::RectWidget::RectWidget(Application* app)
	: Widget(app)
{
}

na::RectWidget::~RectWidget()
{
}

void na::RectWidget::Load(LayoutNode &node)
{
	Widget::Load(node);

	int width = node.GetInt("width", false, m_size.x);
	int height = node.GetInt("height", false, m_size.y);
	SetSize(glm::ivec2(width, height));

	SetColor(node.GetColor("color", false, m_color));
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

		nvgSave(vg);
		nvgBeginPath(vg);
		nvgRect(vg, rect.x, rect.y, rect.z, rect.w);
		nvgFillColor(vg, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a));
		nvgFill(vg);
		nvgRestore(vg);
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
