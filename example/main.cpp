#include <nimble/app.h>
#include <nimble/widgets/rect.h>

using namespace na;

class ExampleApplication : public Application
{
public:
	ExampleApplication()
	{
		RectWidget* root = new RectWidget(this, nullptr);
		root->SetSize(glm::ivec2(32, 32));
		root->SetColor(glm::vec4(1, 0, 0, 1));
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
