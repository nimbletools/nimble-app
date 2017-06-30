#pragma once

#include "common.h"

namespace na
{
	class Application;

	class ContentManager
	{
	private:
		Application* m_app;

	public:
		ContentManager(Application* app);
		~ContentManager();

		int GetFont(const s2::string &name);
		int LoadFont(const s2::string &name, const s2::string &filename);
	};
}
