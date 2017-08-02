#include <nimble/common.h>
#include <nimble/content/nodes/layoutnode.h>

#include <nimble/layoutloader.h>

na::LayoutNode::LayoutNode(LayoutLoader* loader)
{
	m_loader = loader;
}

na::LayoutNode::~LayoutNode()
{
}

const char* na::LayoutNode::GetAttributeValue(const s2::string &name, bool required)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr && required) {
		printf("%s is required, but not given\n", name.c_str());
	}
	return v;
}

const char* na::LayoutNode::GetContentValue()
{
	if (m_loader->Reader->isEmptyElement()) {
		return "";
	}

	while (m_loader->Reader->read()) {
		auto nodeType = m_loader->Reader->getNodeType();

		if (nodeType == irr::io::EXN_TEXT) {
			return m_loader->Reader->getNodeData();
		} else if (nodeType == irr::io::EXN_COMMENT) {
			continue;
		} else {
			return "";
		}
	}

	printf("End of xml document instead of expected content\n");
	return "";
}
