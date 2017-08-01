#pragma once

#include "../../common.h"
#include "../../widget.h"
#include "../managedcode.h"

namespace na
{
	namespace managed_internal
	{
		void Widget_InvalidateLayout(MonoObject* self);
		void Widget_InvalidateRendering(MonoObject* self);

		void Widget_BeginLayoutContainerFlags(MonoObject* self);
		void Widget_BeginLayoutBehaveFlags(MonoObject* self);
		void Widget_BeginLayourMargin(MonoObject* self);
		uint32_t Widget_BeginLayout(MonoObject* self, uint32_t parent);
		glm::ivec4 Widget_GetLayout(MonoObject* self);

		void Widget_Load(MonoObject* self, MonoObject* node);

		void Widget_DoLayout(MonoObject* self, MonoObject* l, uint32_t parent);
		void Widget_Draw(MonoObject* self, MonoObject* g);

		bool Widget_Contains(MonoObject* self, glm::ivec2 absPoint);

		void Widget_OnMouseEnter(MonoObject* self);
		void Widget_OnMouseLeave(MonoObject* self);
		void Widget_OnMouseDown(MonoObject* self, int button);
		void Widget_OnMouseUp(MonoObject* self, int button);

		MonoArray* Widget_GetChildren(MonoObject* self);
		void Widget_AddChild(MonoObject* self, MonoObject* child);

		bool Widget_IsHovering(MonoObject* self);

		MonoString* Widget_GetTagName(MonoObject* self);
		void Widget_SetTagName(MonoObject* self, MonoString* name);

		MonoString* Widget_GetID(MonoObject* self);
		void Widget_SetID(MonoObject* self, MonoString* id);

		MonoString* Widget_GetClass(MonoObject* self);
		void Widget_SetClass(MonoObject* self, MonoString* name);

		bool Widget_IsVisible(MonoObject* self);
		void Widget_SetVisible(MonoObject* self, bool visible);

		WidgetDirection Widget_GetLayoutDirection(MonoObject* self);
		void Widget_SetLayoutDirection(MonoObject* self, WidgetDirection dir);

		WidgetModel Widget_GetLayoutModel(MonoObject* self);
		void Widget_SetLayoutModel(MonoObject* self, WidgetModel model);

		WidgetJustify Widget_GetLayoutJustify(MonoObject* self);
		void Widget_SetLayoutJustify(MonoObject* self, WidgetJustify justify);

		WidgetAnchor Widget_GetLayoutAnchor(MonoObject* self);
		void Widget_SetLayoutAnchor(MonoObject* self, WidgetAnchor anchor);

		bool Widget_IsLayoutWrapping(MonoObject* self);
		void Widget_SetLayoutWrapping(MonoObject* self, bool wrap);

		Bounds Widget_GetMargin(MonoObject* self);
		void Widget_SetMargin(MonoObject* self, Bounds margin);
	}
}
