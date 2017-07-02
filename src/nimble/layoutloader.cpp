#include <nimble/common.h>
#include <nimble/layoutloader.h>
#include <nimble/app.h>
#include <nimble/widget.h>

#include <irrXML.h>

na::LayoutLoader::LayoutLoader(Application* app, irr::io::IrrXMLReader* xml)
{
	m_app = app;
	Reader = xml;
}

na::LayoutLoader::~LayoutLoader()
{
}

void na::LayoutLoader::SkipCurrentNode()
{
	int depth = 1;
	while (Reader->read()) {
		switch (Reader->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				depth++;
				break;

			case irr::io::EXN_ELEMENT_END:
				if (--depth == 0) {
					return;
				}
				break;

			default: break;
		}
	}
}

void na::LayoutLoader::LoadChildren(Widget* parent)
{
	while (Reader->read()) {
		switch (Reader->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				{
					Widget* w = LoadOneWidget();
					if (w != nullptr) {
						parent->AddChild(w);
					}
				}
				break;

			case irr::io::EXN_ELEMENT_END:
				return;

			default: break;
		}
	}
}

na::Widget* na::LayoutLoader::LoadOneWidget()
{
	const char* nodeName = Reader->getNodeName();
	WidgetFactory factory;

	try {
		auto pair = m_app->WidgetFactories.get_pair(nodeName);
		factory = pair.value();
	} catch (s2::dictexception) {
		printf("No factory defined for %s\n", nodeName);
		SkipCurrentNode();
		return nullptr;
	}

	if (factory == nullptr) {
		printf("No factory set for %s\n", nodeName);
		SkipCurrentNode();
		return nullptr;
	}

	LayoutNode node(this);
	na::Widget* w = factory(node);

	if (w == nullptr) {
		printf("Factory for %s returned null\n", nodeName);
		SkipCurrentNode();
		return nullptr;
	}

	LoadChildren(w);
	return w;
}

na::Widget* na::LayoutLoader::Load()
{
	while (Reader->read()) {
		if (Reader->getNodeType() == irr::io::EXN_ELEMENT) {
			return LoadOneWidget();
		}
	}
	return nullptr;
}
