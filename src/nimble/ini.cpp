#include <nimble/common.h>
#include <nimble/ini.h>

#include <nimble/utils.h>

int na::IniPair::AsInt() { return atoi(Value); }
float na::IniPair::AsFloat() { return atof(Value); }
bool na::IniPair::AsBool() { return Value == "true"; }
s2::string na::IniPair::AsString() { return Value; }
glm::ivec2 na::IniPair::AsIvec2() { return ParseIvec2(Value); }
glm::vec2 na::IniPair::AsVec2() { return ParseVec2(Value); }
glm::vec3 na::IniPair::AsVec3() { return ParseVec3(Value); }
glm::vec4 na::IniPair::AsVec4() { return ParseVec4(Value); }
glm::vec4 na::IniPair::AsColor() { return ParseColor(Value); }

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
	if (fh == nullptr) {
		printf("Couldn't load %s\n", filename);
		return;
	}

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
		pair.Value = parse[1].trim();
	}

	fclose(fh);
}
