#include <nimble/common.h>
#include <nimble/utils.h>

uint8_t na::HexToByte(char c)
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

na::Bounds na::ParseBounds(const char* sz)
{
	s2::stringsplit parse(sz, " ");
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

glm::ivec2 na::ParseIvec2(const char* sz)
{
	s2::stringsplit parse(sz, " ");
	if (parse.len() == 1) {
		return glm::ivec2(atoi(parse[0]));
	} else if (parse.len() == 2) {
		return glm::ivec2(atoi(parse[0]), atoi(parse[1]));
	} else {
		printf("Unknown amount of parameters for ivec2: %d\n", (int)parse.len());
	}

	return glm::ivec2();
}

glm::vec2 na::ParseVec2(const char* sz)
{
	s2::stringsplit parse(sz, " ");
	if (parse.len() == 1) {
		return glm::vec2(atof(parse[0]));
	} else if (parse.len() == 2) {
		return glm::vec2(atof(parse[0]), atof(parse[1]));
	} else {
		printf("Unknown amount of parameters for vec2: %d\n", (int)parse.len());
	}

	return glm::vec2();
}

glm::vec3 na::ParseVec3(const char* sz)
{
	s2::stringsplit parse(sz, " ");
	if (parse.len() == 1) {
		return glm::vec3(atof(parse[0]));
	} else if (parse.len() == 3) {
		return glm::vec3(atof(parse[0]), atof(parse[1]), atof(parse[2]));
	} else {
		printf("Unknown amount of parameters for vec3: %d\n", (int)parse.len());
	}

	return glm::vec3();
}

glm::vec4 na::ParseVec4(const char* sz)
{
	s2::stringsplit parse(sz, " ");
	if (parse.len() == 1) {
		return glm::vec4(atof(parse[0]));
	} else if (parse.len() == 4) {
		return glm::vec4(atof(parse[0]), atof(parse[1]), atof(parse[2]), atof(parse[3]));
	} else {
		printf("Unknown amount of parameters for vec4: %d\n", (int)parse.len());
	}

	return glm::vec4();
}

glm::vec4 na::ParseColor(const char* sz)
{
	if (*sz == '#') {
		size_t len = strlen(sz);
		uint8_t r, g, b, a;
		r = g = b = a = 0;

		if (len == 4) {
			// '#f00'
			r = HexToByte(sz[1]); r |= (r << 4);
			g = HexToByte(sz[2]); g |= (g << 4);
			b = HexToByte(sz[3]); b |= (b << 4);
			a = 255;
		} else if (len == 5) {
			// '#f00f'
			r = HexToByte(sz[1]); r |= (r << 4);
			g = HexToByte(sz[2]); g |= (g << 4);
			b = HexToByte(sz[3]); b |= (b << 4);
			a = HexToByte(sz[4]); a |= (a << 4);
		} else if (len == 7) {
			// '#ff0000'
			r = (HexToByte(sz[1]) << 4 | HexToByte(sz[2]));
			g = (HexToByte(sz[3]) << 4 | HexToByte(sz[4]));
			b = (HexToByte(sz[5]) << 4 | HexToByte(sz[6]));
			a = 255;
		} else if (len == 9) {
			// '#ff0000ff'
			r = (HexToByte(sz[1]) << 4 | HexToByte(sz[2]));
			g = (HexToByte(sz[3]) << 4 | HexToByte(sz[4]));
			b = (HexToByte(sz[5]) << 4 | HexToByte(sz[6]));
			a = (HexToByte(sz[7]) << 4 | HexToByte(sz[8]));
		}

		return glm::vec4(
			r / 255.0f,
			g / 255.0f,
			b / 255.0f,
			a / 255.0f
		);

	} else {
		s2::stringsplit parse(sz, " ");
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
