#include <nimble/app.h>

class ExampleApplication : public na::Application
{
public:
	virtual void OnLoad()
	{
		LoadLayout("../content/example.xml");
		LoadStyle("../content/style.ini");
	}
};

int main()
{
	ExampleApplication* app = new ExampleApplication();
	app->Run();
	delete app;

	return 0;
}
