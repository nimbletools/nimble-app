#include <nimble/common.h>
#include <nimble/contentnode.h>

#include <nimble/utils.h>

int na::ContentNode::GetInt(const s2::string &name, bool required, int def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return atoi(v);
}

float na::ContentNode::GetFloat(const s2::string &name, bool required, float def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return atof(v);
}

bool na::ContentNode::GetBool(const s2::string &name, bool required, bool def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return s2::string(v) == "true";
}

s2::string na::ContentNode::GetString(const s2::string &name, bool required, const s2::string &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return s2::string(v);
}

na::Bounds na::ContentNode::GetBounds(const s2::string &name, bool required, const na::Bounds &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseBounds(v);
}

glm::ivec2 na::ContentNode::GetIvec2(const s2::string &name, bool required, const glm::ivec2 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseIvec2(v);
}

glm::vec2 na::ContentNode::GetVec2(const s2::string &name, bool required, const glm::vec2 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec2(v);
}

glm::vec3 na::ContentNode::GetVec3(const s2::string &name, bool required, const glm::vec3 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec3(v);
}

glm::vec4 na::ContentNode::GetVec4(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseVec4(v);
}

glm::vec4 na::ContentNode::GetColor(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = GetAttributeValue(name, required);
	if (v == nullptr) {
		return def;
	}
	return ParseColor(v);
}

s2::string na::ContentNode::GetContent()
{
	return s2::string(GetContentValue()).trim();
}
