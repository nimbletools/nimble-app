#include <nimble/common.h>
#include <nimble/widgets/button.h>
#include <nimble/app.h>
#include <nimble/content/font.h>

#include <nanovg.h>

na::ButtonWidget::ButtonWidget(Application* app)
	: RectWidget(app)
{
	SetColor(glm::vec4(0.3f, 0.3f, 0.3f, 1));
}

na::ButtonWidget::~ButtonWidget()
{
}

void na::ButtonWidget::Load(ContentNode &node)
{
	RectWidget::Load(node);

	if (m_textFont != nullptr) {
		SetFont(node.GetString("font", false, m_textFont->Filename));
	} else {
		SetFont(node.GetString("font"));
	}

	SetTextColor(node.GetColor("textcolor", false, m_textColor));

	SetText(_(node.GetContent(m_text)));
}

void na::ButtonWidget::Draw(NVGcontext* vg)
{
	RectWidget::Draw(vg);

	glm::ivec4 rect = GetLayout();

	if (m_textFont != nullptr && m_text != "") {
		nvgSave(vg);
		nvgFontFaceId(vg, m_textFont->GetHandle());
		nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
		nvgFillColor(vg, nvgRGBAf(m_textColor.r, m_textColor.g, m_textColor.b, m_textColor.a));
		nvgTextBox(vg, (float)rect.x, (float)(rect.y + rect.w / 2.0f), (float)rect.z, m_text, nullptr);
		nvgRestore(vg);
	}
}

void na::ButtonWidget::OnMouseEnter()
{
	SetColor(glm::vec4(0.6f, 0.6f, 0.6f, 1));
	RectWidget::OnMouseEnter();
}

void na::ButtonWidget::OnMouseLeave()
{
	SetColor(glm::vec4(0.3f, 0.3f, 0.3f, 1));
	RectWidget::OnMouseLeave();
}

void na::ButtonWidget::OnMouseDown(int button, const glm::ivec2 &point)
{
	SetColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
	RectWidget::OnMouseDown(button, point);
}

void na::ButtonWidget::OnMouseUp(int button, const glm::ivec2 &point)
{
	if (IsHovering()) {
		SetColor(glm::vec4(0.6f, 0.6f, 0.6f, 1));
	}
	OnClick(this);
	RectWidget::OnMouseUp(button, point);
}

void na::ButtonWidget::SetFont(const s2::string &name)
{
	Font* font = m_app->Content.Get<Font>(name);
	if (m_textFont != font) {
		InvalidateRendering();
	}
	m_textFont = font;
}

void na::ButtonWidget::SetText(const s2::string &text)
{
	if (m_text != text) {
		InvalidateRendering();
	}
	m_text = text;
}

void na::ButtonWidget::SetTextColor(const glm::vec4 &color)
{
	if (m_textColor != color) {
		InvalidateRendering();
	}
	m_textColor = color;
}
