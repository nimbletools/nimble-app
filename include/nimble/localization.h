#pragma once

#include <nimble/common.h>

namespace na
{
	void LoadLocalization(const s2::string &filename);

	s2::string _(s2::string key);
}
