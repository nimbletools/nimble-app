#pragma once

#include "common.h"

namespace na
{
	class IniPair
	{
	public:
		s2::string Key;
		s2::string Value;

	public:
		int AsInt();
		float AsFloat();
		bool AsBool();
		s2::string AsString();
		glm::ivec2 AsIvec2();
		glm::vec2 AsVec2();
		glm::vec3 AsVec3();
		glm::vec4 AsVec4();
		glm::vec4 AsColor();
	};

	class IniSection
	{
	public:
		s2::string Name;
		s2::list<IniPair> Pairs;

	public:
		IniPair* Get(const char* key);
	};

	class Ini : private IniSection
	{
	public:
		s2::list<IniSection> Sections;

	public:
		Ini(const char* filename);

		IniSection* GetSection(const char*  name);

		IniPair* Get(const char* section, const char* key);

	private:
		void Load(const char* filename);
	};
}
