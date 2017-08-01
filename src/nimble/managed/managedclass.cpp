#include <nimble/common.h>
#include <nimble/managed/managedclass.h>

#include <mono/jit/jit.h>

na::ManagedClass::ManagedClass(const char* className)
{
	m_className = className;
}

na::ManagedClass::~ManagedClass()
{
}

void na::ManagedClass::AddInternalCall(const char* methodName, const void* func)
{
	s2::string fullName = s2::strprintf("%s::%s", m_className.c_str(), methodName);
	mono_add_internal_call(fullName, func);
}
