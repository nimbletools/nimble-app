#pragma once

#include "common.h"

namespace na
{
	class Widget;

	enum class WidgetSelectorToken
	{
		Type,
		ID,
		Class,
	};

	class WidgetSelectorExpression
	{
	public:
		WidgetSelectorToken Token;
		s2::string Value;

	public:
		bool Matches(Widget* widget);
	};

	class WidgetSelectorNode
	{
	public:
		s2::list<WidgetSelectorExpression> Expressions;
		s2::list<WidgetSelectorNode> Subnodes;

	private:
		void AddExpression(WidgetSelectorToken token, const char* start, const char* end);

	public:
		void Parse(s2::string query);

		Widget* MatchOne(Widget* container);
		void Match(Widget* container, s2::list<Widget*> &out);
		bool Matches(Widget* widget);
	};
}
