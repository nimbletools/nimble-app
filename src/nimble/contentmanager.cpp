#include <nimble/common.h>
#include <nimble/contentmanager.h>

#include <nimble/app.h>

#include <nanovg.h>

na::ContentManager::ContentManager(Application* app)
{
	m_app = app;
}

na::ContentManager::~ContentManager()
{
}
