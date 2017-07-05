#pragma once

#include "common.h"

#include <irrXML.h>

namespace na
{
	class Application;
	class Widget;

	class LayoutLoader
	{
	private:
		Application* m_app;

	public:
		irr::io::IrrXMLReader* Reader;

	public:
		LayoutLoader(Application* app, irr::io::IrrXMLReader* xml);
		~LayoutLoader();

		void SkipCurrentNode();
		void LoadChildren(Widget* parent);
		Widget* LoadOneWidget();
		Widget* Load();
	};
}
