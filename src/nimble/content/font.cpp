#include <nimble/common.h>
#include <nimble/content/font.h>
#include <nimble/app.h>

#include <nanovg.h>

na::Font::Font(Application* app)
	: Content(app)
{
}

na::Font::~Font()
{
}

void na::Font::Load(const s2::string &filename)
{
	assert(nvgFindFont(m_app->GetNVG(), filename) == -1);

	m_handle = nvgCreateFont(m_app->GetNVG(), filename, filename);
}

int na::Font::GetHandle()
{
	return m_handle;
}
