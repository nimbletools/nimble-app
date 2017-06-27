#include <nimble/app.h>

class ExampleApplication : public na::Application
{
public:
	ExampleApplication()
	{
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
