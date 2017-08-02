#include <nimble/common.h>
#include <nimble/widgets/page.h>

#include <nimble/layoutloader.h>

#include <layout.h>
#include <irrXML.h>

na::PageWidget::PageWidget(Application* app, const s2::string &layoutFnm)
	: Widget(app)
{
	LoadLayout(layoutFnm);
	SetLayoutAnchor(WidgetAnchor::AnchorFill);
}

na::PageWidget::~PageWidget()
{
}

void na::PageWidget::DoLayout(lay_context* l, lay_id parent)
{
	lay_id id = BeginLayout(parent);

	Widget::DoLayout(l, id);
}

void na::PageWidget::LoadLayout(const s2::string &filename)
{
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(filename);
	if (xml == nullptr) {
		printf("Couldn't open %s\n", (const char*)filename);
		return;
	}

	LayoutLoader loader(m_app, xml);
	AddChild(loader.Load());

	delete xml;
}

bool na::PageWidget::DrawBehind()
{
	return false;
}

bool na::PageWidget::InputBehind()
{
	return false;
}

na::PageAction::PageAction(PageActionType type, PageWidget* page)
{
	m_type = type;
	m_page = page;
}
