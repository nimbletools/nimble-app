#pragma once

#include "../common.h"
#include "rect.h"
#include "../content/font.h"

namespace na
{
	class ButtonWidget : public RectWidget
	{
	private:
		EventOnClick m_funcOnClick;

		s2::string m_text;
		Font* m_textFont = nullptr;
		glm::vec4 m_textColor = glm::vec4(1, 1, 1, 1);

	public:
		ButtonWidget(Application* app);
		virtual ~ButtonWidget();

		virtual void Draw(NVGcontext* vg);

		virtual void OnMouseEnter();
		virtual void OnMouseLeave();
		virtual void OnMouseDown(int button);
		virtual void OnMouseUp(int button);

		virtual void SetFont(const s2::string &name);
		virtual void SetText(const s2::string &text);

		virtual void FuncOnClick(const EventOnClick &func);
	};
}
