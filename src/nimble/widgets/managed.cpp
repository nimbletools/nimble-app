#include <nimble/widgets/managed.h>

na::ManagedWidget::ManagedWidget(Application* app, MonoObject* obj)
	: Widget(app)
{
	m_object = obj;
}

na::ManagedWidget::~ManagedWidget()
{
}
