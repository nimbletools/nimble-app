#pragma once

#include "common.h"

namespace na
{
	class Bounds
	{
	public:
		int m_left = 0;
		int m_right = 0;
		int m_top = 0;
		int m_bottom = 0;

	public:
		Bounds();
		Bounds(const Bounds &copy);
		Bounds(int all);
		Bounds(int horizontal, int vertical);
		Bounds(int left, int right, int top, int bottom);

		bool operator==(const Bounds &other) const;
		bool operator!=(const Bounds &other) const;
	};
}
