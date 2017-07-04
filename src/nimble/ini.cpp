#include <nimble/common.h>
#include <nimble/ini.h>

#include <nimble/utils.h>

int na::IniPair::AsInt() { return atoi(m_value); }
float na::IniPair::AsFloat() { return atof(m_value); }
bool na::IniPair::AsBool() { return m_value == "true"; }
s2::string na::IniPair::AsString() { return m_value; }
glm::ivec2 na::IniPair::AsIvec2() { return ParseIvec2(m_value); }
glm::vec2 na::IniPair::AsVec2() { return ParseVec2(m_value); }
glm::vec3 na::IniPair::AsVec3() { return ParseVec3(m_value); }
glm::vec4 na::IniPair::AsVec4() { return ParseVec4(m_value); }
glm::vec4 na::IniPair::AsColor() { return ParseColor(m_value); }

na::IniPair* na::IniSection::Get(const char* key)
{
	for (IniPair &pair : Pairs) {
		if (pair.Key == key) {
			return &pair;
		}
	}
	return nullptr;
}

na::Ini::Ini(const char* filename)
{
	Name = filename;
	Load(filename);
}

na::IniSection* na::Ini::GetSection(const char* name)
{
	for (IniSection &section : Sections) {
		if (section.Name == name) {
			return &section;
		}
	}
	return nullptr;
}

na::IniPair* na::Ini::Get(const char* section, const char* key)
{
	IniSection* s = GetSection(section);
	if (s == nullptr) {
		return nullptr;
	}
	return s->Get(key);
}

void na::Ini::Load(const char* filename)
{
	FILE* fh = fopen(filename, "rb");

	IniSection* currentSection = (IniSection*)this;

	char line[512];
	while (fgets(line, 512, fh) != nullptr) {
		if (*line == ';' || *line == '#') {
			continue;
		}

		char* endl = strchr(line, '\r');
		if (endl == nullptr) {
			endl = strchr(line, '\n');
		}
		if (endl != nullptr) {
			*endl = '\0';
		}

		if (endl == line) {
			continue;
		}

		if (*line == '[') {
			currentSection = &Sections.add();
			currentSection->Name = s2::string(line).trim(" []");\
			continue;
		}

		s2::stringsplit parse(line, "=", 2);
		if (parse.len() != 2) {
			printf("Invalid line: \"%s\"\n", line);
			continue;
		}

		IniPair &pair = currentSection->Pairs.add();
		pair.Key = parse[0].trim();
		pair.m_value = parse[1].trim();
	}

	fclose(fh);
}
