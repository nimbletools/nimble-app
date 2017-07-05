#pragma once

#include "../common.h"
#include "../widget.h"
#include "../content/font.h"

namespace na
{
	//TODO: Move this to some generic text rendering place
	enum class TextAlignH
	{
		Left,
		Center,
		Right
	};

	enum class TextAlignV
	{
		Top,
		Middle,
		Bottom
	};

	class LabelWidget : public Widget
	{
	private:
		s2::string m_text;
		Font* m_font = nullptr;
		float m_fontSize = 16.0f;
		glm::vec4 m_color = glm::vec4(1, 1, 1, 1);
		TextAlignH m_alignH = TextAlignH::Left;
		TextAlignV m_alignV = TextAlignV::Top;

		bool m_autoSize = true;
		glm::ivec2 m_size;

	public:
		LabelWidget(Application* app);
		virtual ~LabelWidget();

		virtual void Load(ContentNode &node);

		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		inline const s2::string &GetText() { return m_text; }
		virtual void SetText(const s2::string &text);

		inline Font* GetFont() { return m_font; }
		virtual void SetFont(const s2::string &name);

		inline float GetFontSize() { return m_fontSize; }
		virtual void SetFontSize(float fontSize);

		inline const glm::vec4 &GetColor() { return m_color; }
		virtual void SetColor(const glm::vec4 &color);

		inline TextAlignH GetAlignH() { return m_alignH; }
		virtual void SetAlignH(TextAlignH align);

		inline TextAlignV GetAlignV() { return m_alignV; }
		virtual void SetAlignV(TextAlignV align);

		inline bool GetAutosize() { return m_autoSize; }
		virtual void SetAutosize(bool autosize);

		inline const glm::ivec2 &GetSize() { return m_size; }
		virtual void SetSize(const glm::ivec2 &size);
	};
}
