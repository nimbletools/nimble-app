#include <nimble/common.h>
#include <nimble/managed/managedcode.h>
#include <nimble/managed/managedclass.h>
#include <nimble/managed/internal/widget.h>
#include <nimble/managed/internal/contentnode.h>
#include <nimble/widgets/managed.h>

na::ManagedCode::ManagedCode(na::Application* app)
{
	m_app = app;
}

na::ManagedCode::~ManagedCode()
{
	Uninitialize();
}

void na::ManagedCode::Initialize()
{
	printf("Initializing Mono jit\n");

	mono_set_dirs("managed", "managed");
	m_domain = mono_jit_init("NimbleApp");

	m_assemblyNimbleApp = mono_domain_assembly_open(m_domain, "Nimble.App.dll");
	if (m_assemblyNimbleApp == nullptr) {
		printf("Failed to open assembly Nimble.App.dll!\n");
		Uninitialize();
		return;
	}

	MonoImage* image = mono_assembly_get_image(m_assemblyNimbleApp);
	MonoClass* classLoader = mono_class_from_name(image, "Nimble.App.Internal", "EntryPoint");
	MonoMethod* methodInitialize = mono_class_get_method_from_name(classLoader, "Initialize", 0);

	MonoObject* exc = nullptr;
	mono_runtime_invoke(methodInitialize, nullptr, nullptr, &exc);
	if (exc != nullptr) {
		mono_print_unhandled_exception(exc);
		printf("Managed initialization failed!\n");
		Uninitialize();
		return;
	}

	InitializeInternalCalls();
}

void na::ManagedCode::Uninitialize()
{
	if (m_domain != nullptr) {
		mono_jit_cleanup(m_domain);
		m_domain = nullptr;
	}
}

na::Widget* na::ManagedCode::LoadWidget(const char* tag)
{
	MonoImage* image = mono_assembly_get_image(m_assemblyNimbleApp);
	MonoClass* classLoader = mono_class_from_name(image, "Nimble.App.Internal", "WidgetLoader");
	MonoMethod* method = mono_class_get_method_from_name(classLoader, "FindWidgetType", 1);

	void* args[1];
	args[0] = mono_string_new(m_domain, tag);

	MonoReflectionType* type = (MonoReflectionType*)mono_runtime_invoke(method, nullptr, args, nullptr);
	if (type == nullptr) {
		return nullptr;
	}

	MonoClass* cls = mono_type_get_class(mono_reflection_type_get_type(type));
	MonoObject* obj = mono_object_new(m_domain, cls);

	if (obj == nullptr) {
		return nullptr;
	}

	ManagedWidget* ret = new ManagedWidget(m_app, obj);

	SetManagedPtr(obj, ret);
	mono_runtime_object_init(obj);

	return ret;
}

void na::ManagedCode::SetManagedPtr(MonoObject* obj, void* p)
{
	MonoClass* cls = mono_object_get_class(obj);
	MonoClassField* field = mono_class_get_field_from_name(cls, "__Ptr");
	if (field == nullptr) {
		printf("WARNING: Couldn't find __Ptr to get on %s.%s\n", mono_class_get_namespace(cls), mono_class_get_name(cls));
		return;
	}
	mono_field_set_value(obj, field, &p);
}

void na::ManagedCode::InitializeInternalCalls()
{
	ManagedClass widget("Nimble.App.Widgets.Widget");

	widget.AddInternalCall("InvalidateLayout", &na::managed_internal::Widget_InvalidateLayout);
	widget.AddInternalCall("InvalidateRendering", &na::managed_internal::Widget_InvalidateRendering);

	widget.AddInternalCall("BeginLayoutContainerFlags", &na::managed_internal::Widget_BeginLayoutContainerFlags);
	widget.AddInternalCall("BeginLayoutBehaveFlags", &na::managed_internal::Widget_BeginLayoutBehaveFlags);
	widget.AddInternalCall("BeginLayourMargin", &na::managed_internal::Widget_BeginLayourMargin);
	widget.AddInternalCall("BeginLayout", &na::managed_internal::Widget_BeginLayout);
	widget.AddInternalCall("GetLayout", &na::managed_internal::Widget_GetLayout);

	widget.AddInternalCall("Load", &na::managed_internal::Widget_Load);

	widget.AddInternalCall("DoLayout", &na::managed_internal::Widget_DoLayout);
	widget.AddInternalCall("Draw", &na::managed_internal::Widget_Draw);

	widget.AddInternalCall("Contains", &na::managed_internal::Widget_Contains);

	widget.AddInternalCall("OnMouseEnter", &na::managed_internal::Widget_OnMouseEnter);
	widget.AddInternalCall("OnMouseLeave", &na::managed_internal::Widget_OnMouseLeave);
	widget.AddInternalCall("OnMouseDown", &na::managed_internal::Widget_OnMouseDown);
	widget.AddInternalCall("OnMouseUp", &na::managed_internal::Widget_OnMouseUp);

	widget.AddInternalCall("GetChildren", &na::managed_internal::Widget_GetChildren);
	widget.AddInternalCall("AddChild", &na::managed_internal::Widget_AddChild);

	widget.AddInternalCall("IsHovering", &na::managed_internal::Widget_IsHovering);

	widget.AddInternalCall("GetTagName", &na::managed_internal::Widget_GetTagName);
	widget.AddInternalCall("SetTagName", &na::managed_internal::Widget_SetTagName);

	widget.AddInternalCall("GetID", &na::managed_internal::Widget_GetID);
	widget.AddInternalCall("SetID", &na::managed_internal::Widget_SetID);

	widget.AddInternalCall("GetClass", &na::managed_internal::Widget_GetClass);
	widget.AddInternalCall("SetClass", &na::managed_internal::Widget_SetClass);

	widget.AddInternalCall("IsVisible", &na::managed_internal::Widget_IsVisible);
	widget.AddInternalCall("SetVisible", &na::managed_internal::Widget_SetVisible);

	widget.AddInternalCall("GetLayoutDirection", &na::managed_internal::Widget_GetLayoutDirection);
	widget.AddInternalCall("SetLayoutDirection", &na::managed_internal::Widget_SetLayoutDirection);

	widget.AddInternalCall("GetLayoutModel", &na::managed_internal::Widget_GetLayoutModel);
	widget.AddInternalCall("SetLayoutModel", &na::managed_internal::Widget_SetLayoutModel);

	widget.AddInternalCall("GetLayoutJustify", &na::managed_internal::Widget_GetLayoutJustify);
	widget.AddInternalCall("SetLayoutJustify", &na::managed_internal::Widget_SetLayoutJustify);

	widget.AddInternalCall("GetLayoutAnchor", &na::managed_internal::Widget_GetLayoutAnchor);
	widget.AddInternalCall("SetLayoutAnchor", &na::managed_internal::Widget_SetLayoutAnchor);

	widget.AddInternalCall("IsLayoutWrapping", &na::managed_internal::Widget_IsLayoutWrapping);
	widget.AddInternalCall("SetLayoutWrapping", &na::managed_internal::Widget_SetLayoutWrapping);

	widget.AddInternalCall("GetMargin", &na::managed_internal::Widget_GetMargin);
	widget.AddInternalCall("SetMargin", &na::managed_internal::Widget_SetMargin);

	ManagedClass contentNode("Nimble.App.Serialization.ContentNode");

	contentNode.AddInternalCall("GetInt", &na::managed_internal::ContentNode_GetInt);
	contentNode.AddInternalCall("GetFloat", &na::managed_internal::ContentNode_GetFloat);
	contentNode.AddInternalCall("GetBool", &na::managed_internal::ContentNode_GetBool);
	contentNode.AddInternalCall("GetString", &na::managed_internal::ContentNode_GetString);
	contentNode.AddInternalCall("GetBounds", &na::managed_internal::ContentNode_GetBounds);
	contentNode.AddInternalCall("GetIvec2", &na::managed_internal::ContentNode_GetIvec2);
	contentNode.AddInternalCall("GetVec2", &na::managed_internal::ContentNode_GetVec2);
	contentNode.AddInternalCall("GetVec3", &na::managed_internal::ContentNode_GetVec3);
	contentNode.AddInternalCall("GetVec4", &na::managed_internal::ContentNode_GetVec4);
	contentNode.AddInternalCall("GetColor", &na::managed_internal::ContentNode_GetColor);

	contentNode.AddInternalCall("GetContent", &na::managed_internal::ContentNode_GetContent);

}
