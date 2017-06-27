#include <nimble/app.h>
#include <nimble/widgets/rect.h>

using namespace na;

class ExampleApplication : public Application
{
public:
	ExampleApplication()
	{
		RectWidget* root = new RectWidget(this);
		root->SetLayoutDirection(WidgetDirection::Horizontal);
		root->SetLayoutAnchor(AnchorFill);
		root->SetColor(glm::vec4(0.2f, 0, 0, 1));

		RectWidget* list = new RectWidget(this);
		list->SetLayoutDirection(WidgetDirection::Vertical);
		list->SetLayoutAnchor(AnchorLeft | AnchorFillV);
		list->SetSize(glm::ivec2(300, 0));
		list->SetColor(glm::vec4(0, 0.2f, 0, 1));
		list->SetMargin(Bounds(6));

		root->AddChild(list);

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
