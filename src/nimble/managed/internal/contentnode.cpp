#include <nimble/common.h>
#include <nimble/managed/internal/contentnode.h>

int na::managed_internal::ContentNode_GetInt(MonoObject* self, MonoString* name, bool required, int def)
{
	ContentNode* node = ManagedCode::GetManagedPtr<ContentNode>(self);
	//
	return def;
}
float na::managed_internal::ContentNode_GetFloat(MonoObject* self, MonoString* name, bool required, float def)
{
	//
	return def;
}
bool na::managed_internal::ContentNode_GetBool(MonoObject* self, MonoString* name, bool required, bool def)
{
	//
	return def;
}
MonoString* na::managed_internal::ContentNode_GetString(MonoObject* self, MonoString* name, bool required, MonoString* def)
{
	//
	return def;
}
na::Bounds na::managed_internal::ContentNode_GetBounds(MonoObject* self, MonoString* name, bool required, Bounds def)
{
	//
	return def;
}
glm::ivec2 na::managed_internal::ContentNode_GetIvec2(MonoObject* self, MonoString* name, bool required, glm::ivec2 def)
{
	//
	return def;
}
glm::vec2 na::managed_internal::ContentNode_GetVec2(MonoObject* self, MonoString* name, bool required, glm::vec2 def)
{
	//
	return def;
}
glm::vec3 na::managed_internal::ContentNode_GetVec3(MonoObject* self, MonoString* name, bool required, glm::vec3 def)
{
	//
	return def;
}
glm::vec4 na::managed_internal::ContentNode_GetVec4(MonoObject* self, MonoString* name, bool required, glm::vec4 def)
{
	//
	return def;
}
glm::vec4 na::managed_internal::ContentNode_GetColor(MonoObject* self, MonoString* name, bool required, glm::vec4 def)
{
	//
	return def;
}

MonoString* na::managed_internal::ContentNode_GetContent(MonoObject* self, MonoString* def)
{
	//
	return def;
}
