#pragma once

#include "common.h"

namespace na
{
	class Application;

	class Content
	{
	protected:
		Application* m_app;

	public:
		s2::string Filename;

	protected:
		Content(Application* app);

	public:
		virtual ~Content();

		virtual void Load(const s2::string &filename) = 0;
	};
}
