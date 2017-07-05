#pragma once

#include "../../common.h"
#include "../../contentnode.h"

namespace na
{
	class IniSection;

	class StyleNode : public ContentNode
	{
	private:
		IniSection* m_section;

	public:
		StyleNode(IniSection* section);
		virtual ~StyleNode();

		virtual const char* GetAttributeValue(const s2::string &name, bool required);
		virtual const char* GetContentValue();
	};
}
