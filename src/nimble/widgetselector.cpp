#include <nimble/common.h>
#include <nimble/widgetselector.h>

#include <nimble/widget.h>

bool na::WidgetSelectorExpression::Matches(na::Widget* widget)
{
	switch (Token) {
		case WidgetSelectorToken::Type: return widget->GetTagName() == Value;
		case WidgetSelectorToken::ID: return widget->GetID() == Value;
		case WidgetSelectorToken::Class: return widget->GetClass() == Value;
	}

	printf("Unknown widget selector token %d\n", (int)Token);
	return false;
}

void na::WidgetSelectorNode::AddExpression(WidgetSelectorToken token, const char* start, const char* end)
{
	if (start == end) {
		return;
	}

	WidgetSelectorExpression &expr = Expressions.add();
	expr.Token = token;
	expr.Value = s2::string(start, end - start);
}

void na::WidgetSelectorNode::Parse(s2::string query)
{
	const char* p = query;

	char* pnext = const_cast<char*>(strchr(p, ' '));
	if (pnext != nullptr) {
		*pnext = '\0';
		pnext++;
	}

	WidgetSelectorToken token = WidgetSelectorToken::Type;
	const char* pstart = p;

	const char* pp = p;
	while (*pp != '\0') {
		if (*pp == '#') {
			AddExpression(token, pstart, pp);
			token = WidgetSelectorToken::ID;
			pstart = pp + 1;

		} else if (*pp == '.') {
			AddExpression(token, pstart, pp);
			token = WidgetSelectorToken::Class;
			pstart = pp + 1;
		}

		pp++;
	}

	AddExpression(token, pstart, pp);

	if (pnext != nullptr) {
		WidgetSelectorNode &newSubnode = Subnodes.add();
		newSubnode.Parse(pnext);
	}
}

na::Widget* na::WidgetSelectorNode::MatchOne(Widget* container)
{
	for (Widget* child : container->GetChildren()) {
		if (!Matches(child)) {
			Widget* ret = MatchOne(child);
			if (ret != nullptr) {
				return ret;
			}
			continue;
		}

		if (Subnodes.len() > 0) {
			for (WidgetSelectorNode &subnode : Subnodes) {
				Widget* ret = subnode.MatchOne(child);
				if (ret != nullptr) {
					return ret;
				}
			}
		} else {
			return child;
		}
	}
	return nullptr;
}

void na::WidgetSelectorNode::Match(Widget* container, s2::list<Widget*> &out)
{
	for (Widget* child : container->GetChildren()) {
		if (!Matches(child)) {
			Match(child, out);
			continue;
		}

		if (Subnodes.len() > 0) {
			for (WidgetSelectorNode &subnode : Subnodes) {
				subnode.Match(child, out);
			}
		} else {
			out.add(child);
		}
	}
}

bool na::WidgetSelectorNode::Matches(Widget* widget)
{
	for (WidgetSelectorExpression &expr : Expressions) {
		if (!expr.Matches(widget)) {
			return false;
		}
	}
	return true;
}
