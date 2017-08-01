#pragma once

#include "../common.h"

namespace na
{
	class ManagedClass
	{
	private:
		s2::string m_className;

	public:
		ManagedClass(const char* className);
		~ManagedClass();

		void AddInternalCall(const char* methodName, const void* func);
	};
}
