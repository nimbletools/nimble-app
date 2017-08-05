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

float na::Font::GetNextGlyphOffset(const char* pch, float size)
{
	NVGcontext* vg = m_app->GetNVG();

	BeginMeasureMode(size);

	NVGglyphPosition pos[2];
	nvgTextGlyphPositions(vg, 0, 0, pch, nullptr, pos, 2);

	EndMeasureMode();

	return pos[1].x;
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

void na::Font::BeginMeasureMode(float size)
{
	NVGcontext* vg = m_app->GetNVG();
	nvgSave(vg);
	nvgReset(vg); //TODO: why is this needed?
	nvgFontFaceId(vg, m_handle);
	nvgFontSize(vg, size);
	nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
}

glm::vec2 na::Font::MeasureNow(const s2::string &text)
{
	return MeasureNow(text, text.len());
}

glm::vec2 na::Font::MeasureNow(const s2::string &text, int len)
{
	NVGcontext* vg = m_app->GetNVG();
	float bounds[4];
	nvgTextBounds(vg, 0, 0, text, (const char*)text + len, bounds);
	return glm::vec2(bounds[2], bounds[3]);
}

void na::Font::EndMeasureMode()
{
	NVGcontext* vg = m_app->GetNVG();
	nvgRestore(vg);
}
