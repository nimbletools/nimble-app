#pragma once

#include "common.h"
#include "contentnode.h"

namespace na
{
	class LayoutLoader;

	class LayoutNode : public ContentNode
	{
	private:
		LayoutLoader* m_loader;

	public:
		LayoutNode(LayoutLoader* loader);
		virtual ~LayoutNode();

		virtual const char* GetAttributeValue(const s2::string &name, bool required);
		virtual const char* GetContentValue();
	};
}
