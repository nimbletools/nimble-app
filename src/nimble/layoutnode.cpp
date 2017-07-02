#include <nimble/common.h>
#include <nimble/layoutnode.h>

#include <nimble/layoutloader.h>

static uint8_t hextobyte(char c)
{
	c = (char)tolower(c);
	if (c >= '0' && c <= '9') {
		return (uint8_t)(c - '0');
	}
	if (c >= 'a' && c <= 'f') {
		return (uint8_t)(0xA + (c - 'a'));
	}
	return 0;
}

na::LayoutNode::LayoutNode(LayoutLoader* loader)
{
	m_loader = loader;
}

na::LayoutNode::~LayoutNode()
{
}

int na::LayoutNode::GetInt(const s2::string &name, bool required, int def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}
	return atoi(v);
}

float na::LayoutNode::GetFloat(const s2::string &name, bool required, float def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}
	return atof(v);
}

bool na::LayoutNode::GetBool(const s2::string &name, bool required, bool def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}
	return s2::string(v) == "true";
}

s2::string na::LayoutNode::GetString(const s2::string &name, bool required, const s2::string &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}
	return s2::string(v);
}

na::Bounds na::LayoutNode::GetBounds(const s2::string &name, bool required, const na::Bounds &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}

	s2::stringsplit parse(v, " ");
	if (parse.len() == 1) {
		return Bounds(atoi(parse[0]));
	} else if (parse.len() == 2) {
		return Bounds(atoi(parse[0]), atoi(parse[1]));
	} else if (parse.len() == 4) {
		return Bounds(atoi(parse[0]), atoi(parse[1]), atoi(parse[2]), atoi(parse[3]));
	} else {
		printf("Unknown amount of parameters for bounds: %d\n", (int)parse.len());
	}

	return Bounds(0);
}

glm::vec2 na::LayoutNode::GetVec2(const s2::string &name, bool required, const glm::vec2 &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}

	s2::stringsplit parse(v, " ");
	if (parse.len() == 1) {
		return glm::vec2(atof(parse[0]));
	} else if (parse.len() == 2) {
		return glm::vec2(atof(parse[0]), atof(parse[1]));
	} else {
		printf("Unknown amount of parameters for vec2: %d\n", (int)parse.len());
	}

	return glm::vec2();
}

glm::vec3 na::LayoutNode::GetVec3(const s2::string &name, bool required, const glm::vec3 &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}

	s2::stringsplit parse(v, " ");
	if (parse.len() == 1) {
		return glm::vec3(atof(parse[0]));
	} else if (parse.len() == 3) {
		return glm::vec3(atof(parse[0]), atof(parse[1]), atof(parse[2]));
	} else {
		printf("Unknown amount of parameters for vec3: %d\n", (int)parse.len());
	}

	return glm::vec3();
}

glm::vec4 na::LayoutNode::GetVec4(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}

	s2::stringsplit parse(v, " ");
	if (parse.len() == 1) {
		return glm::vec4(atof(parse[0]));
	} else if (parse.len() == 4) {
		return glm::vec4(atof(parse[0]), atof(parse[1]), atof(parse[2]), atof(parse[3]));
	} else {
		printf("Unknown amount of parameters for vec4: %d\n", (int)parse.len());
	}

	return glm::vec4();
}

glm::vec4 na::LayoutNode::GetColor(const s2::string &name, bool required, const glm::vec4 &def)
{
	const char* v = m_loader->Reader->getAttributeValue(name);
	if (v == nullptr) {
		if (required) {
			printf("%s is required, but not given\n", (const char*)name);
		}
		return def;
	}

	if (*v == '#') {
		size_t len = strlen(v);
		uint8_t r, g, b, a;
		r = g = b = a = 0;

		if (len == 4) {
			// '#f00'
			r = hextobyte(v[1]); r |= (r << 4);
			g = hextobyte(v[2]); g |= (g << 4);
			b = hextobyte(v[3]); b |= (b << 4);
			a = 255;
		} else if (len == 5) {
			// '#f00f'
			r = hextobyte(v[1]); r |= (r << 4);
			g = hextobyte(v[2]); g |= (g << 4);
			b = hextobyte(v[3]); b |= (b << 4);
			a = hextobyte(v[4]); a |= (a << 4);
		} else if (len == 7) {
			// '#ff0000'
			r = (hextobyte(v[1]) << 4 | hextobyte(v[2]));
			g = (hextobyte(v[3]) << 4 | hextobyte(v[4]));
			b = (hextobyte(v[5]) << 4 | hextobyte(v[6]));
			a = 255;
		} else if (len == 9) {
			// '#ff0000ff'
			r = (hextobyte(v[1]) << 4 | hextobyte(v[2]));
			g = (hextobyte(v[3]) << 4 | hextobyte(v[4]));
			b = (hextobyte(v[5]) << 4 | hextobyte(v[6]));
			a = (hextobyte(v[7]) << 4 | hextobyte(v[8]));
		}

		return glm::vec4(
			r / 255.0f,
			g / 255.0f,
			b / 255.0f,
			a / 255.0f
		);

	} else {
		s2::stringsplit parse(v, " ");
		if (parse.len() == 1) {
			return glm::vec4(atof(parse[0]));
		} else if (parse.len() == 4) {
			return glm::vec4(atof(parse[0]), atof(parse[1]), atof(parse[2]), atof(parse[3]));
		} else {
			printf("Unknown amount of parameters for color: %d\n", (int)parse.len());
		}
	}

	return glm::vec4();
}

s2::string na::LayoutNode::GetContent()
{
	while (m_loader->Reader->read()) {
		auto nodeType = m_loader->Reader->getNodeType();

		if (nodeType == irr::io::EXN_TEXT) {
			return s2::string(m_loader->Reader->getNodeData()).trim();
		} else if (nodeType == irr::io::EXN_COMMENT) {
			continue;
		} else {
			return "";
		}
	}

	printf("End of xml document instead of expected content\n");
	return "";
}
