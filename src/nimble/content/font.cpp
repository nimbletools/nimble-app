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

glm::vec2 na::Font::Measure(const s2::string &text, float size)
{
	NVGcontext* vg = m_app->GetNVG();

	nvgSave(vg);
	nvgReset(vg); //TODO: why is this needed?
	nvgFontFaceId(vg, m_handle);
	nvgFontSize(vg, size);
	nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
	float bounds[4];
	nvgTextBounds(vg, 0, 0, text, nullptr, bounds);
	nvgRestore(vg);

	return glm::vec2(bounds[2], bounds[3]);
}
