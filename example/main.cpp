#include <nimble/app.h>
#include <nimble/widgets/rect.h>

using namespace na;

class ExampleApplication : public Application
{
public:
	ExampleApplication()
	{
		RectWidget* root = new RectWidget(this, nullptr);
		root->SetLayoutDirection(WidgetDirection::Horizontal);
		root->SetLayoutAnchor(WidgetAnchor::Fill);
		root->SetColor(glm::vec4(0.2f, 0, 0, 1));
		SetRoot(root);
	}

	~ExampleApplication()
	{
	}
};

int main()
{
	ExampleApplication* app = new ExampleApplication();
	app->Run();
	delete app;

	return 0;
}
