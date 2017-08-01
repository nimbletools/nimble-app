#pragma once

#include "../common.h"
#include "../widget.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace na
{
	class ManagedCode
	{
	private:
		Application* m_app;

		MonoDomain* m_domain = nullptr;
		MonoAssembly* m_assemblyNimbleApp = nullptr;

		s2::list<MonoClass*> m_widgetClasses;

	public:
		ManagedCode(Application* app);
		~ManagedCode();

		void Initialize();
		void Uninitialize();

		na::Widget* LoadWidget(const char* tag);

		static void SetManagedPtr(MonoObject* obj, void* p);

		template<typename T>
		static inline T* GetManagedPtr(MonoObject* obj)
		{
			static MonoClassField* field = nullptr;

			if (obj == nullptr) {
				return nullptr;
			}

			if (field == nullptr) {
				MonoClass* cls = mono_object_get_class(obj);
				field = mono_class_get_field_from_name(cls, "__Ptr");

				if (field == nullptr) {
					printf("WARNING: Couldn't find __Ptr field to set on %s.%s\n", mono_class_get_namespace(cls), mono_class_get_name(cls));
					return nullptr;
				}
			} else {
				//TODO: Make sure the field belongs to the right class
				//TODO: Only do that in debug builds for optimization sake?
			}

			void* ret = nullptr;
			mono_field_get_value(obj, field, &ret);
			return (T*)ret;
		}

	private:
		void InitializeInternalCalls();
	};
}
