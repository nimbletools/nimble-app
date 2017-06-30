#include <nimble/common.h>
#include <nimble/widgets/label.h>
#include <nimble/app.h>

#include <layout.h>
#include <nanovg.h>

na::LabelWidget::LabelWidget(Application* app)
	: Widget(app)
{
}

na::LabelWidget::~LabelWidget()
{
}

void na::LabelWidget::DoLayout(lay_context* l, lay_id parent)
{
	lay_id id = BeginLayout(parent);

	if (m_autoSize && m_font != nullptr) {
		glm::vec2 measure = m_font->Measure(m_text, m_fontSize);
		m_size = glm::ivec2((int)measure.x, (int)measure.y);
	}

	lay_set_size_xy(l, id, m_size.x, m_size.y);

	Widget::DoLayout(l, id);
}

void na::LabelWidget::Draw(NVGcontext* vg)
{
	if (m_font != nullptr && m_color.a > 0.0f) {
		glm::ivec4 rect = GetLayout();

		nvgSave(vg);
		nvgFontFaceId(vg, m_font->GetHandle());
		int align = 0;
		switch (m_alignH) {
			case TextAlignH::Left: align |= NVG_ALIGN_LEFT; break;
			case TextAlignH::Center: align |= NVG_ALIGN_CENTER; break;
			case TextAlignH::Right: align |= NVG_ALIGN_RIGHT; break;
		}
		switch (m_alignV) {
			case TextAlignV::Top: align |= NVG_ALIGN_TOP; break;
			case TextAlignV::Middle: align |= NVG_ALIGN_MIDDLE; break;
			case TextAlignV::Bottom: align |= NVG_ALIGN_BOTTOM; break;
		}
		nvgTextAlign(vg, align);
		nvgFontSize(vg, m_fontSize);
		nvgFillColor(vg, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a));
		nvgTextBox(vg, rect.x, rect.y, rect.z, m_text, nullptr);
		nvgRestore(vg);
	}

	Widget::Draw(vg);
}

void na::LabelWidget::SetText(const s2::string &text)
{
	if (m_text != text) {
		if (m_autoSize) {
			InvalidateLayout();
		} else {
			InvalidateRendering();
		}
	}
	m_text = text;
}

void na::LabelWidget::SetFont(const s2::string &name)
{
	Font* font = m_app->Content.Get<Font>(name);
	if (m_font != font) {
		if (m_autoSize) {
			InvalidateLayout();
		} else {
			InvalidateRendering();
		}
	}
	m_font = font;
}

void na::LabelWidget::SetFontSize(float fontSize)
{
	if (m_fontSize != fontSize) {
		if (m_autoSize) {
			InvalidateLayout();
		} else {
			InvalidateRendering();
		}
	}
	m_fontSize = fontSize;
}

void na::LabelWidget::SetColor(const glm::vec4 &color)
{
	if (m_color != color) {
		InvalidateRendering();
	}
	m_color = color;
}

void na::LabelWidget::SetAlignH(TextAlignH align)
{
	if (m_alignH != align) {
		InvalidateRendering();
	}
	m_alignH = align;
}

void na::LabelWidget::SetAlignV(TextAlignV align)
{
	if (m_alignV != align) {
		InvalidateRendering();
	}
	m_alignV = align;
}

void na::LabelWidget::SetAutosize(bool autosize)
{
	if (m_autoSize != autosize) {
		InvalidateLayout();
	}
	m_autoSize = autosize;
}

void na::LabelWidget::SetSize(const glm::ivec2 &size)
{
	if (m_size != size) {
		InvalidateLayout();
	}
	m_size = size;
}
