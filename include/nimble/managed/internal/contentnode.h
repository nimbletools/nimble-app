#include "../../common.h"
#include "../managedcode.h"

namespace na
{
	namespace managed_internal
	{
		int ContentNode_GetInt(MonoObject* self, MonoString* name, bool required, int def);
		float ContentNode_GetFloat(MonoObject* self, MonoString* name, bool required, float def);
		bool ContentNode_GetBool(MonoObject* self, MonoString* name, bool required, bool def);
		MonoString* ContentNode_GetString(MonoObject* self, MonoString* name, bool required, MonoString* def);
		Bounds ContentNode_GetBounds(MonoObject* self, MonoString* name, bool required, Bounds def);
		glm::ivec2 ContentNode_GetIvec2(MonoObject* self, MonoString* name, bool required, glm::ivec2 def);
		glm::vec2 ContentNode_GetVec2(MonoObject* self, MonoString* name, bool required, glm::vec2 def);
		glm::vec3 ContentNode_GetVec3(MonoObject* self, MonoString* name, bool required, glm::vec3 def);
		glm::vec4 ContentNode_GetVec4(MonoObject* self, MonoString* name, bool required, glm::vec4 def);
		glm::vec4 ContentNode_GetColor(MonoObject* self, MonoString* name, bool required, glm::vec4 def);

		MonoString* ContentNode_GetContent(MonoObject* self, MonoString* def);
	}
}
