#include <nimble/common.h>
#include <nimble/layoutnode.h>

#include <nimble/layoutloader.h>
#include <nimble/utils.h>

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

int na::LayoutNode::GetInt(const s2::string &name, bool required, int def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return atoi(v);
}

float na::LayoutNode::GetFloat(const s2::string &name, bool required, float def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return atof(v);
}

bool na::LayoutNode::GetBool(const s2::string &name, bool required, bool def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return s2::string(v) == "true";
}

s2::string na::LayoutNode::GetString(const s2::string &name, bool required, const s2::string &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return s2::string(v);
}

na::Bounds na::LayoutNode::GetBounds(const s2::string &name, bool required, const na::Bounds &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseBounds(v);
}

glm::ivec2 na::LayoutNode::GetIvec2(const s2::string &name, bool required, const glm::ivec2 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseIvec2(v);
}

glm::vec2 na::LayoutNode::GetVec2(const s2::string &name, bool required, const glm::vec2 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec2(v);
}

glm::vec3 na::LayoutNode::GetVec3(const s2::string &name, bool required, const glm::vec3 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec3(v);
}

glm::vec4 na::LayoutNode::GetVec4(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec4(v);
}

glm::vec4 na::LayoutNode::GetColor(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseColor(v);
}

s2::string na::LayoutNode::GetContent()
{
	return s2::string(GetContentValue()).trim();
}
