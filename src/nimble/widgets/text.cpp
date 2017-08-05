#include <nimble/common.h>

#include <nimble/app.h>
#include <nimble/widgets/text.h>

#include <GLFW/glfw3.h>
#include <layout.h>
#include <nanovg.h>

#define STB_TEXTEDIT_K_KEYDOWN    0x80000000
#define STB_TEXTEDIT_K_SHIFT      0x40000000
#define STB_TEXTEDIT_K_CONTROL    0x20000000

static void TES_LayoutRow(StbTexteditRow* row, na::TextWidget* obj, int n)
{
	//TODO: Multiline word-wrapping!

	// Here, `n` is the position within the string that this row starts at

	na::Font* font = obj->GetFont();
	float fontSize = obj->GetFontSize();
	const s2::string &text = obj->GetText();

	assert(font != nullptr);

	glm::vec2 size = font->MeasureNow(text);

	// X start, X end (required for wordwrapping, but also useful for text alignment)
	row->x0 = 0;
	row->x1 = size.x;

	// Y distance from previous row (should be fontSize if we're not doing any kind of rich text or 0 if this is the first line)
	row->baseline_y_delta = 0;
	row->ymin = 0;
	row->ymax = fontSize;

	// Number of chars in this row
	row->num_chars = (int)text.len();
}

static float TES_GetWidth(na::TextWidget* obj, int n, int i)
{
	// Here, `n` is the position within the string that this row starts at
	// We return the pixel distance between char (n + i) and (n + i + 1)

	//TODO: If this is a monospaced font, we could just return some constant

	na::Font* font = obj->GetFont();
	const char* sz = obj->GetText();

	return font->GetNextGlyphOffset(sz + n + i, obj->GetFontSize());
}

static bool TES_InsertChars(na::TextWidget* obj, int i, const char* sz, int n)
{
	return obj->InsertChars(i, sz, n);
}

#define STB_TEXTEDIT_STRING                     na::TextWidget
#define STB_TEXTEDIT_STRINGLEN(obj)             ((int)(obj)->GetText().len())
#define STB_TEXTEDIT_LAYOUTROW                  TES_LayoutRow
#define STB_TEXTEDIT_GETWIDTH                   TES_GetWidth
#define STB_TEXTEDIT_KEYTOTEXT(k)               (((k) & STB_TEXTEDIT_K_KEYDOWN) ? 0 : (k))
#define STB_TEXTEDIT_GETCHAR(obj, i)            ((obj)->GetText()[i])
#define STB_TEXTEDIT_NEWLINE                    ('\n')
#define STB_TEXTEDIT_DELETECHARS(obj, i, n)     ((obj)->DeleteChars(i, n))
#define STB_TEXTEDIT_INSERTCHARS                TES_InsertChars

#define STB_TEXTEDIT_K_LEFT       STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_LEFT
#define STB_TEXTEDIT_K_RIGHT      STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_RIGHT
#define STB_TEXTEDIT_K_UP         STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_UP
#define STB_TEXTEDIT_K_DOWN       STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_DOWN
#define STB_TEXTEDIT_K_LINESTART  STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_HOME
#define STB_TEXTEDIT_K_LINEEND    STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_END
#define STB_TEXTEDIT_K_TEXTSTART  STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_HOME
#define STB_TEXTEDIT_K_TEXTEND    STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_END
#define STB_TEXTEDIT_K_DELETE     STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_DELETE
#define STB_TEXTEDIT_K_BACKSPACE  STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_BACKSPACE
#define STB_TEXTEDIT_K_UNDO       STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_Z
#define STB_TEXTEDIT_K_REDO       STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_Y
#define STB_TEXTEDIT_K_INSERT     STB_TEXTEDIT_K_KEYDOWN | GLFW_KEY_INSERT
#define STB_TEXTEDIT_K_WORDLEFT   STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_LEFT
#define STB_TEXTEDIT_K_WORDRIGHT  STB_TEXTEDIT_K_KEYDOWN | STB_TEXTEDIT_K_CONTROL | GLFW_KEY_RIGHT

#define STB_TEXTEDIT_IS_SPACE(ch) (isspace(ch) != 0)

#define STB_TEXTEDIT_IMPLEMENTATION
#include <stb_textedit.h>

na::TextWidget::TextWidget(Application* app)
	: Widget(app)
{
}

na::TextWidget::~TextWidget()
{
}

void na::TextWidget::Load(ContentNode &node)
{
	Widget::Load(node);

	SetCursor(Cursor::Ibeam);

	if (m_font != nullptr) {
		SetFont(node.GetString("font", false, m_font->Filename));
	} else {
		SetFont(node.GetString("font"));
	}

	SetFontSize(node.GetFloat("fontsize", false, m_fontSize));

	int width = node.GetInt("width", false, m_size.x);
	int height = node.GetInt("height", false, m_size.y);
	SetSize(glm::ivec2(width, height));

	SetColor(node.GetColor("color", false, m_color));
	SetTextColor(node.GetColor("textcolor", false, m_colorText));
	SetSelectionColor(node.GetColor("selectioncolor", false, m_colorSelection));

	SetMultiline(node.GetBool("multiline", false, m_multiline));

	SetText(_(node.GetContent(m_text)));

	//TODO: Invalidate text edit state when SetMultiline is called?
	stb_textedit_initialize_state(&m_textEditState, m_multiline ? 1 : 0);
	memcpy(&m_textEditStatePrev, &m_textEditState, sizeof(STB_TexteditState));
}

void na::TextWidget::DoLayout(lay_context* l, lay_id parent)
{
	lay_id id = BeginLayout(parent);

	lay_set_size_xy(l, id, m_size.x, m_size.y);

	Widget::DoLayout(l, parent);
}

void na::TextWidget::Draw(NVGcontext* vg)
{
	if (m_font == nullptr) {
		return;
	}

	glm::ivec4 rect = GetLayout();

	nvgSave(vg);
	nvgReset(vg);

	if (m_color.a > 0.0f) {
		nvgBeginPath(vg);
		nvgRect(vg, (float)rect.x, (float)rect.y, (float)rect.z, (float)rect.w);
		nvgFillColor(vg, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a));
		nvgFill(vg);

		if (HasFocus()) {
			nvgStrokeWidth(vg, 1);
			nvgStrokeColor(vg, nvgRGBAf(0.2f, 0.2f, 1.0f, 1.0f));
			nvgStroke(vg);
		}

		nvgClosePath(vg);
	}

	if (m_colorText.a > 0.0f) {
		nvgScissor(vg, (float)rect.x, (float)rect.y, (float)rect.z, (float)rect.w);

		nvgFontFaceId(vg, m_font->GetHandle());
		nvgFontSize(vg, m_fontSize);
		nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);

		float cursorX = 0;
		float cursorY = 0;
		float cursorWidth = 0;
		float selStartX = 0;
		float selEndX = 0;

		float lastX = 0;
		const int numPos = 10;
		NVGglyphPosition pos[numPos + 1];
		for (int i = 0; i < (int)m_text.len(); i += numPos) {
			int npos = nvgTextGlyphPositions(vg, lastX, 0, (const char*)m_text + i, nullptr, pos, numPos + 1);

			int cursorIndex = m_textEditState.cursor - i;
			if (cursorIndex <= numPos && cursorIndex >= 0) {
				if (cursorIndex == npos) {
					cursorX = pos[cursorIndex - 1].maxx;
					cursorWidth = 0;
				} else {
					cursorX = pos[cursorIndex].x;
					cursorWidth = pos[cursorIndex].maxx - cursorX;
				}
			}

			int selStartIndex = m_textEditState.select_start - i;
			if (selStartIndex <= numPos && selStartIndex >= 0) {
				if (selStartIndex == npos) {
					selStartX = pos[selStartIndex - 1].maxx;
				} else {
					selStartX = pos[selStartIndex].x;
				}
			}

			int selEndIndex = m_textEditState.select_end - i;
			if (selEndIndex <= numPos && selEndIndex >= 0) {
				if (selEndIndex == npos) {
					selEndX = pos[selEndIndex - 1].maxx;
				} else {
					selEndX = pos[selEndIndex].x;
				}
			}

			lastX = pos[numPos].x;
		}

		nvgFillColor(vg, nvgRGBAf(m_colorSelection.r, m_colorSelection.g, m_colorSelection.b, m_colorSelection.a));
		nvgBeginPath(vg);
		nvgRect(vg, (float)rect.x + selStartX, (float)rect.y, selEndX - selStartX, m_fontSize);
		nvgFill(vg);
		nvgClosePath(vg);

		nvgFillColor(vg, nvgRGBAf(m_colorText.r, m_colorText.g, m_colorText.b, m_colorText.a));
		nvgText(vg, (float)rect.x, (float)rect.y, m_text, nullptr);

		if (HasFocus()) {
			nvgBeginPath(vg);

			if (m_textEditState.insert_mode == 0 || cursorWidth == 0) {
				// Insert mode
				nvgRect(vg, rect.x + cursorX, rect.y + cursorY, 1, m_fontSize);
			} else {
				// Overwrite mode
				nvgRect(vg, rect.x + cursorX, rect.y + cursorY + m_fontSize, cursorWidth, 1);
			}

			nvgFill(vg);
			nvgClosePath(vg);
		}
	}

	nvgRestore(vg);

	Widget::Draw(vg);
}

void na::TextWidget::CheckTextEditStateChanged()
{
	if (memcmp(&m_textEditStatePrev, &m_textEditState, sizeof(STB_TexteditState) - sizeof(StbUndoState)) == 0) {
		return;
	}
	memcpy(&m_textEditStatePrev, &m_textEditState, sizeof(STB_TexteditState) - sizeof(StbUndoState));
	InvalidateRendering();
}

void na::TextWidget::OnMouseDown(int button, const glm::ivec2 &point)
{
	Widget::OnMouseDown(button, point);

	if (button == GLFW_MOUSE_BUTTON_1 && m_font != nullptr) {
		m_font->BeginMeasureMode(m_fontSize);

		m_dragging = true;
		stb_textedit_click(this, &m_textEditState, (float)point.x, (float)point.y);

		m_font->EndMeasureMode();
		CheckTextEditStateChanged();
	}
}

void na::TextWidget::OnMouseMove(const glm::ivec2 &point)
{
	Widget::OnMouseMove(point);

	if (m_dragging && m_font != nullptr) {
		m_font->BeginMeasureMode(m_fontSize);

		stb_textedit_drag(this, &m_textEditState, (float)point.x, (float)point.y);

		m_font->EndMeasureMode();
		CheckTextEditStateChanged();
	}
}

void na::TextWidget::OnMouseUp(int button, const glm::ivec2 &point)
{
	Widget::OnMouseUp(button, point);

	if (button == GLFW_MOUSE_BUTTON_1) {
		m_dragging = false;
	}
}

bool na::TextWidget::CanHaveFocus()
{
	return true;
}

void na::TextWidget::OnFocus()
{
	InvalidateRendering();
}

void na::TextWidget::OnFocusLost()
{
	InvalidateRendering();
}

void na::TextWidget::OnKeyPress(int key, int scancode, int mods)
{
	if (mods & GLFW_MOD_SHIFT) {
		key |= STB_TEXTEDIT_K_SHIFT;
	}

	if (mods & GLFW_MOD_CONTROL) {
		key |= STB_TEXTEDIT_K_CONTROL;
	}

	key |= STB_TEXTEDIT_K_KEYDOWN;

	m_font->BeginMeasureMode(m_fontSize);

	stb_textedit_key(this, &m_textEditState, key);

	m_font->EndMeasureMode();
	CheckTextEditStateChanged();
}

void na::TextWidget::OnChar(unsigned int ch, int mods)
{
	if (mods & GLFW_MOD_SHIFT) {
		ch |= STB_TEXTEDIT_K_SHIFT;
	}

	m_font->BeginMeasureMode(m_fontSize);

	stb_textedit_key(this, &m_textEditState, (int)ch);

	m_font->EndMeasureMode();
	CheckTextEditStateChanged();
}

void na::TextWidget::SetText(const s2::string &text)
{
	if (m_text != text) {
		InvalidateRendering();
	}
	m_text = text;

	stb_textedit_clamp(this, &m_textEditState);
	CheckTextEditStateChanged();
}

void na::TextWidget::SetFont(const s2::string &name)
{
	Font* font = m_app->Content.Get<Font>(name);
	if (m_font != font) {
		InvalidateRendering();
	}
	m_font = font;
}

void na::TextWidget::SetFontSize(float fontSize)
{
	if (m_fontSize != fontSize) {
		InvalidateRendering();
	}
	m_fontSize = fontSize;
}

void na::TextWidget::SetSize(const glm::ivec2 &size)
{
	if (m_size != size) {
		InvalidateLayout();
	}
	m_size = size;
}

void na::TextWidget::SetColor(const glm::vec4 &color)
{
	if (m_color != color) {
		InvalidateRendering();
	}
	m_color = color;
}

void na::TextWidget::SetTextColor(const glm::vec4 &color)
{
	if (m_colorText != color) {
		InvalidateRendering();
	}
	m_colorText = color;
}

void na::TextWidget::SetSelectionColor(const glm::vec4 &color)
{
	if (m_colorSelection != color) {
		InvalidateRendering();
	}
	m_colorSelection = color;
}

void na::TextWidget::SetMultiline(bool multiline)
{
	if (m_multiline != multiline) {
		InvalidateRendering();
	}
	m_multiline = multiline;
}

bool na::TextWidget::DeleteChars(int i, int num)
{
	m_text.remove(i, num);
	InvalidateRendering();
	return true;
}

bool na::TextWidget::InsertChars(int i, const char* sz, int num)
{
	m_text.insert(sz, i, num);
	InvalidateRendering();
	return true;
}
