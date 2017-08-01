#pragma once

#include "../common.h"
#include "rect.h"
#include "../content/font.h"

namespace na
{
	class ButtonWidget : public RectWidget
	{
	private:
		s2::string m_text;
		Font* m_textFont = nullptr;
		glm::vec4 m_textColor = glm::vec4(1, 1, 1, 1);

	public:
		EventList OnClick;

	public:
		ButtonWidget(Application* app);
		virtual ~ButtonWidget();

		virtual void Load(ContentNode &node);

		virtual void Draw(NVGcontext* vg);

		virtual void OnMouseEnter();
		virtual void OnMouseLeave();
		virtual void OnMouseDown(int button);
		virtual void OnMouseUp(int button);

		inline Font* GetFont() { return m_textFont; }
		virtual void SetFont(const s2::string &name);

		inline const s2::string &GetText() { return m_text; }
		virtual void SetText(const s2::string &text);

		inline const glm::vec4 &GetTextColor() { return m_textColor; }
		virtual void SetTextColor(const glm::vec4 &color);
	};
}
