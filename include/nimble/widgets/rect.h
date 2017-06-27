#pragma once

#include "../common.h"
#include "../widget.h"

namespace na
{
	class RectWidget : public Widget
	{
	private:
		glm::ivec2 m_size;
		glm::vec4 m_color;

	public:
		RectWidget(Application* app, Widget* parent);
		virtual ~RectWidget();

		virtual void DoLayout(lay_context* l, lay_id parent);
		virtual void Draw(NVGcontext* vg);

		inline glm::ivec2 GetSize() { return m_size; }
		virtual void SetSize(const glm::ivec2 &size);

		inline glm::vec4 GetColor() { return m_color; }
		virtual void SetColor(const glm::vec4 &color);
	};
}
