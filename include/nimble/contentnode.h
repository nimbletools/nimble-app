#pragma once

#include "common.h"
#include "utils/bounds.h"

namespace na
{
	class ContentNode
	{
	public:
		virtual const char* GetAttributeValue(const s2::string &name, bool required) = 0;
		virtual const char* GetContentValue() = 0;

		int GetInt(const s2::string &name, bool required = true, int def = 0);
		float GetFloat(const s2::string &name, bool required = true, float def = 0.0f);
		bool GetBool(const s2::string &name, bool required = true, bool def = false);
		s2::string GetString(const s2::string &name, bool required = true, const s2::string &def = "");
		Bounds GetBounds(const s2::string &name, bool required = true, const Bounds &def = Bounds(0));
		glm::ivec2 GetIvec2(const s2::string &name, bool required = true, const glm::ivec2 &def = glm::ivec2());
		glm::vec2 GetVec2(const s2::string &name, bool required = true, const glm::vec2 &def = glm::vec2());
		glm::vec3 GetVec3(const s2::string &name, bool required = true, const glm::vec3 &def = glm::vec3());
		glm::vec4 GetVec4(const s2::string &name, bool required = true, const glm::vec4 &def = glm::vec4());
		glm::vec4 GetColor(const s2::string &name, bool required = true, const glm::vec4 &def = glm::vec4());

		s2::string GetContent(const s2::string &def = "");
	};
}
