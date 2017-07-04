#pragma once

#include "common.h"
#include "bounds.h"

namespace na
{
	uint8_t HexToByte(char c);

	Bounds ParseBounds(const char* sz);
	glm::ivec2 ParseIvec2(const char* sz);
	glm::vec2 ParseVec2(const char* sz);
	glm::vec3 ParseVec3(const char* sz);
	glm::vec4 ParseVec4(const char* sz);
	glm::vec4 ParseColor(const char* sz);
}
