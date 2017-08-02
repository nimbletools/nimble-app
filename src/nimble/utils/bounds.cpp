#include <nimble/utils/bounds.h>

na::Bounds::Bounds()
{
}

na::Bounds::Bounds(const Bounds &copy)
{
	m_left = copy.m_left;
	m_right = copy.m_right;
	m_top = copy.m_top;
	m_bottom = copy.m_bottom;
}

na::Bounds::Bounds(int all)
{
	m_left = m_right = m_top = m_bottom = all;
}

na::Bounds::Bounds(int horizontal, int vertical)
{
	m_left = m_right = horizontal;
	m_top = m_bottom = vertical;
}

na::Bounds::Bounds(int left, int right, int top, int bottom)
{
	m_left = left;
	m_right = right;
	m_top = top;
	m_bottom = bottom;
}

bool na::Bounds::operator==(const Bounds &other) const
{
	return
	  (m_left == other.m_left) &&
	  (m_right == other.m_right) &&
	  (m_top == other.m_top) &&
	  (m_bottom == other.m_bottom);
}

bool na::Bounds::operator!=(const Bounds &other) const
{
	return !(operator==(other));
}
