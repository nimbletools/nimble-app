#include <nimble/common.h>
#include <nimble/utils/localization.h>
#include <nimble/utils/ini.h>

static s2::dict<s2::string, s2::dict<s2::string, s2::string>> _strings;

void na::LoadLocalization(const s2::string &filename)
{
	_strings.clear();

	na::Ini inifile(filename);
	for (auto &iniSection : inifile.Sections) {
		auto &section = _strings.add(iniSection.Name).value();
		for (auto &pair : iniSection.Pairs) {
			section.add(pair.Key, pair.AsString());
		}
	}
}

s2::string na::_(s2::string key)
{
	if (!key.startswith("##")) {
		return key;
	}

	key = key.substr(2);

	try {
		s2::stringsplit parse = key.split(".", 2);
		s2::string section, value;
		if (parse.len() == 1) {
			value = parse[0];
		} else {
			section = parse[0];
			value = parse[1];
		}
		auto &stringsSection = _strings.get_pair(section).value();
		return stringsSection.get_pair(value).value();
	} catch (s2::dictexception) {
		return s2::strprintf("#!ERROR:%s", key.c_str());
	}
}
