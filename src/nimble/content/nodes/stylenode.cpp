#include <nimble/common.h>
#include <nimble/content/nodes/stylenode.h>

#include <nimble/ini.h>

na::StyleNode::StyleNode(IniSection* section)
{
	m_section = section;
}

na::StyleNode::~StyleNode()
{
}

const char* na::StyleNode::GetAttributeValue(const s2::string &name, bool required)
{
	IniPair* pair = m_section->Get(name);
	if (pair == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", name.c_str());
		}
		return nullptr;
	}
	return pair->Value;
}

const char* na::StyleNode::GetContentValue()
{
	return nullptr;
}
