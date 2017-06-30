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

int na::ContentManager::GetFont(const s2::string &name)
{
	return nvgFindFont(m_app->m_nvg, name);
}

int na::ContentManager::LoadFont(const s2::string &name, const s2::string &filename)
{
	int ret = nvgFindFont(m_app->m_nvg, name);
	if (ret == -1) {
		ret = nvgCreateFont(m_app->m_nvg, name, filename);
		if (ret == -1) {
			printf("Failed to create font\n");
		}
	}
	return ret;
}
