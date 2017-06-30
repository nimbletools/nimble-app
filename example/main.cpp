#include <nimble/app.h>
#include <nimble/widgets/rect.h>
#include <nimble/widgets/button.h>

using namespace na;

class ExampleApplication : public Application
{
public:
	virtual void OnLoad()
	{
		Content.LoadFont("Roboto", "Roboto.ttf");

		RectWidget* root = new RectWidget(this);
		root->SetLayoutDirection(WidgetDirection::Horizontal);
		root->SetLayoutAnchor(AnchorFill);
		root->SetColor(glm::vec4(0.2f, 0, 0, 1));

		RectWidget* list = new RectWidget(this);
		list->SetLayoutDirection(WidgetDirection::Vertical);
		list->SetLayoutAnchor(AnchorLeft | AnchorFillV);
		list->SetSize(glm::ivec2(300, 0));
		list->SetColor(glm::vec4(0, 0.2f, 0, 1));
		list->SetMargin(Bounds(5));
		root->AddChild(list);

		RectWidget* content = new RectWidget(this);
		content->SetLayoutDirection(WidgetDirection::Horizontal);
		content->SetLayoutWrapping(true);
		content->SetLayoutAnchor(AnchorFill);
		root->AddChild(content);

		for (int i = 0; i < 5; i++) {
			ButtonWidget* button = new ButtonWidget(this);
			button->SetFont("Roboto");
			button->SetText(s2::strprintf("Button %d", i));
			button->SetSize(glm::ivec2(290, 30));
			button->SetMargin(Bounds(5));
			button->FuncOnClick([i, content, this]() {
				if (i == 4) {
					SetSize(512, 512);
					return;
				}

				RectWidget* rect = new RectWidget(this);
				rect->SetSize(glm::ivec2(32, 32));
				rect->SetColor(glm::vec4(0, 1, 0, 1));
				rect->SetMargin(Bounds(5));
				content->AddChild(rect);
			});
			list->AddChild(button);
		}

		SetRoot(root);
	}
};

int main()
{
	ExampleApplication* app = new ExampleApplication();
	app->Run();
	delete app;

	return 0;
}
