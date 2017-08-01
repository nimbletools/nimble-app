#include <nimble/common.h>
#include <nimble/managed/internal/widget.h>
#include <nimble/widgets/managed.h>
#include <nimble/app.h>

void na::managed_internal::Widget_InvalidateLayout(MonoObject* self)
{
	Widget* w = ManagedCode::GetManagedPtr<Widget>(self);
	if (w == nullptr) { return; }
	w->InvalidateLayout();
}
void na::managed_internal::Widget_InvalidateRendering(MonoObject* self)
{
	Widget* w = ManagedCode::GetManagedPtr<Widget>(self);
	if (w == nullptr) { return; }
	w->InvalidateRendering();
}

void na::managed_internal::Widget_BeginLayoutContainerFlags(MonoObject* self)
{
	//
}
void na::managed_internal::Widget_BeginLayoutBehaveFlags(MonoObject* self)
{
	//
}
void na::managed_internal::Widget_BeginLayourMargin(MonoObject* self)
{
	//
}
uint32_t na::managed_internal::Widget_BeginLayout(MonoObject* self, uint32_t parent)
{
	//
	return 0;
}
glm::ivec4 na::managed_internal::Widget_GetLayout(MonoObject* self)
{
	//
	return glm::ivec4();
}

void na::managed_internal::Widget_Load(MonoObject* self, MonoObject* node)
{
	//
}

void na::managed_internal::Widget_DoLayout(MonoObject* self, MonoObject* l, uint32_t parent)
{
	//
}
void na::managed_internal::Widget_Draw(MonoObject* self, MonoObject* g)
{
	//
}

bool na::managed_internal::Widget_Contains(MonoObject* self, glm::ivec2 absPoint)
{
	//
	return false;
}

void na::managed_internal::Widget_OnMouseEnter(MonoObject* self)
{
	//
}
void na::managed_internal::Widget_OnMouseLeave(MonoObject* self)
{
	//
}
void na::managed_internal::Widget_OnMouseDown(MonoObject* self, int button)
{
	//
}
void na::managed_internal::Widget_OnMouseUp(MonoObject* self, int button)
{
	//
}

MonoArray* na::managed_internal::Widget_GetChildren(MonoObject* self)
{
	//
	return nullptr;
}
void na::managed_internal::Widget_AddChild(MonoObject* self, MonoObject* child)
{
	//
}

bool na::managed_internal::Widget_IsHovering(MonoObject* self)
{
	//
	return false;
}

MonoString* na::managed_internal::Widget_GetTagName(MonoObject* self)
{
	//
	return nullptr;
}
void na::managed_internal::Widget_SetTagName(MonoObject* self, MonoString* name)
{
	//
}

MonoString* na::managed_internal::Widget_GetID(MonoObject* self)
{
	//
	return nullptr;
}
void na::managed_internal::Widget_SetID(MonoObject* self, MonoString* id)
{
	//
}

MonoString* na::managed_internal::Widget_GetClass(MonoObject* self)
{
	//
	return nullptr;
}
void na::managed_internal::Widget_SetClass(MonoObject* self, MonoString* name)
{
	//
}

bool na::managed_internal::Widget_IsVisible(MonoObject* self)
{
	//
	return false;
}
void na::managed_internal::Widget_SetVisible(MonoObject* self, bool visible)
{
	//
}

na::WidgetDirection na::managed_internal::Widget_GetLayoutDirection(MonoObject* self)
{
	//
	return WidgetDirection::None;
}
void na::managed_internal::Widget_SetLayoutDirection(MonoObject* self, WidgetDirection dir)
{
	//
}

na::WidgetModel na::managed_internal::Widget_GetLayoutModel(MonoObject* self)
{
	//
	return WidgetModel::Layout;
}
void na::managed_internal::Widget_SetLayoutModel(MonoObject* self, WidgetModel model)
{
	//
}

na::WidgetJustify na::managed_internal::Widget_GetLayoutJustify(MonoObject* self)
{
	//
	return WidgetJustify::Start;
}
void na::managed_internal::Widget_SetLayoutJustify(MonoObject* self, WidgetJustify justify)
{
	//
}

na::WidgetAnchor na::managed_internal::Widget_GetLayoutAnchor(MonoObject* self)
{
	//
	return WidgetAnchor::AnchorNone;
}
void na::managed_internal::Widget_SetLayoutAnchor(MonoObject* self, WidgetAnchor anchor)
{
	//
}

bool na::managed_internal::Widget_IsLayoutWrapping(MonoObject* self)
{
	//
	return false;
}
void na::managed_internal::Widget_SetLayoutWrapping(MonoObject* self, bool wrap)
{
	//
}

na::Bounds na::managed_internal::Widget_GetMargin(MonoObject* self)
{
	//
	return Bounds();
}
void na::managed_internal::Widget_SetMargin(MonoObject* self, Bounds margin)
{
	//
}
