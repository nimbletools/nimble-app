#pragma once

#include "../common.h"
#include "../content.h"

namespace na
{
	class Font : public Content
	{
	private:
		int m_handle;

	public:
		Font(Application* app);
		virtual ~Font();

		virtual void Load(const s2::string &filename);

		int GetHandle();

		float GetNextGlyphOffset(const char* pch, float size = 16.0f);

		glm::vec2 Measure(const s2::string &text, float size = 16.0f);

		void BeginMeasureMode(float size = 16.0f);
		glm::vec2 MeasureNow(const s2::string &text);
		glm::vec2 MeasureNow(const s2::string &text, int len);
		void EndMeasureMode();
	};
}
