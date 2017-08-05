#pragma once

#include "../common.h"
#include "../widget.h"
#include "../content/font.h"

#define STB_TEXTEDIT_CHARTYPE char
#include <stb_textedit.h>

namespace na
{
	class TextWidget : public Widget
	{
	private:
		s2::string m_text;
		Font* m_font = nullptr;
		float m_fontSize = 16.0f;
		glm::ivec2 m_size;
		glm::vec4 m_color = glm::vec4(0, 0, 0, 1);
		glm::vec4 m_colorText = glm::vec4(1, 1, 1, 1);
		bool m_multiline = false;

		STB_TexteditState m_textEditState;
		bool m_dragging = false;

	public:
		TextWidget(Application* app);
		virtual ~TextWidget();

		virtual void Load(ContentNode &node);

		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		virtual void OnMouseDown(int button, const glm::ivec2 &point);
		virtual void OnMouseMove(const glm::ivec2 &point);
		virtual void OnMouseUp(int button, const glm::ivec2 &point);

		virtual bool CanHaveFocus();
		virtual void OnFocus();
		virtual void OnFocusLost();

		virtual void OnKeyPress(int key, int scancode, int mods);
		virtual void OnChar(unsigned int ch, int mods);

		inline const s2::string &GetText() { return m_text; }
		virtual void SetText(const s2::string &text);

		inline Font* GetFont() { return m_font; }
		virtual void SetFont(const s2::string &name);

		inline float GetFontSize() { return m_fontSize; }
		virtual void SetFontSize(float fontSize);

		inline const glm::ivec2 &GetSize() { return m_size; }
		virtual void SetSize(const glm::ivec2 &size);

		inline const glm::vec4 &GetColor() { return m_color; }
		virtual void SetColor(const glm::vec4 &color);

		inline const glm::vec4 &GetTextColor() { return m_colorText; }
		virtual void SetTextColor(const glm::vec4 &color);

		inline bool IsMultiline() { return m_multiline; }
		virtual void SetMultiline(bool multiline);

		virtual bool DeleteChars(int i, int num);
		virtual bool InsertChars(int i, const char* sz, int num);
	};
}
