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

		glm::vec2 Measure(const s2::string &text, float size = 16.0f);
	};
}
