#include <nimble/app.h>
#include <nimble/widgets/button.h>

class ExamplePage : public na::PageWidget
{
public:
	ExamplePage(na::Application* app) : PageWidget(app, "content/example.xml")
	{
		auto wContainer = Selector<na::ButtonWidget>("#container");

		auto buttonCreateBlock = Selector<na::ButtonWidget>("#create_block");
		if (buttonCreateBlock != nullptr) {
			buttonCreateBlock->OnClick.add([this, wContainer](na::Widget* sender, na::WidgetEvent e) {
				if (wContainer == nullptr) {
					return;
				}
				auto newRect = new na::RectWidget(m_app);
				newRect->SetColor(glm::vec4(1, 0, 0, 1));
				newRect->SetMargin(na::Bounds(4));
				newRect->SetSize(glm::ivec2(32, 32));
				wContainer->AddChild(newRect);
			});
		}

		auto buttonInvalidateLayout = Selector<na::ButtonWidget>("#invalidate_layout");
		if (buttonInvalidateLayout != nullptr) {
			buttonInvalidateLayout->OnClick.add([this](na::Widget* sender, na::WidgetEvent e) {
				InvalidateLayout();
			});
		}

		auto buttonResizeWindow = Selector<na::ButtonWidget>("#resize_window");
		if (buttonResizeWindow != nullptr) {
			buttonResizeWindow->OnClick.add([this](na::Widget* sender, na::WidgetEvent e) {
				m_app->SetWindowSize(glm::ivec2(1600, 900));
			});
		}
	}
};

class ExampleApplication : public na::Application
{
public:
	virtual void OnLoad()
	{
		PushPage(new ExamplePage(this));
	}
};

int main()
{
	na::LoadLocalization("content/english.ini");

	ExampleApplication* app = new ExampleApplication();
	app->Run();
	delete app;

	return 0;
}
