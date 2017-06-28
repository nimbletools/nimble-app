#include <nimble/common.h>
#include <nimble/widgets/button.h>

#include <nanovg.h>

na::ButtonWidget::ButtonWidget(Application* app)
	: RectWidget(app)
{
	SetColor(glm::vec4(0.3f, 0.3f, 0.3f, 1));
}

na::ButtonWidget::~ButtonWidget()
{
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

void na::ButtonWidget::OnMouseDown(int button)
{
	SetColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
	RectWidget::OnMouseDown(button);
}

void na::ButtonWidget::OnMouseUp(int button)
{
	if (IsHovering()) {
		SetColor(glm::vec4(0.6f, 0.6f, 0.6f, 1));
	}
	RectWidget::OnMouseUp(button);
}
