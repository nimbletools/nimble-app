using Nimble.App.Math;
using Nimble.App.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Widgets
{
	public class Widget
	{
		internal IntPtr __Ptr;

		[MethodImpl(MethodImplOptions.InternalCall)] protected extern void InvalidateLayout();
		[MethodImpl(MethodImplOptions.InternalCall)] protected extern void InvalidateRendering();

		[MethodImpl(MethodImplOptions.InternalCall)] protected extern void BeginLayoutContainerFlags();
		[MethodImpl(MethodImplOptions.InternalCall)] protected extern void BeginLayoutBehaveFlags();
		[MethodImpl(MethodImplOptions.InternalCall)] protected extern void BeginLayourMargin();
		[MethodImpl(MethodImplOptions.InternalCall)] protected extern uint BeginLayout(uint parent);
		[MethodImpl(MethodImplOptions.InternalCall)] protected extern Vector4Int GetLayout();

		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void Load(ContentNode node);

		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void DoLayout(WidgetLayout l, uint parent);
		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void Draw(WidgetGraphics g);

		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern bool Contains(Vector2Int absPoint);

		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void OnMouseEnter();
		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void OnMouseLeave();
		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void OnMouseDown(int button);
		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void OnMouseUp(int button);

		[MethodImpl(MethodImplOptions.InternalCall)] public extern Widget[] GetChildren();
		[MethodImpl(MethodImplOptions.InternalCall)] public virtual extern void AddChild(Widget child);

		[MethodImpl(MethodImplOptions.InternalCall)] private extern bool IsHovering();
		public bool Hovering
		{
			get { return IsHovering(); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern string GetTagName();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetTagName(string name);
		public string TagName
		{
			get { return GetTagName(); }
			set { SetTagName(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern string GetID();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetID(string id);
		public string ID
		{
			get { return GetID(); }
			set { SetID(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern string GetClass();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetClass(string name);
		public string Class
		{
			get { return GetClass(); }
			set { SetClass(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern bool IsVisible();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetVisible(bool visible);
		public bool Visible
		{
			get { return IsVisible(); }
			set { SetVisible(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern WidgetDirection GetLayoutDirection();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetLayoutDirection(WidgetDirection dir);
		public WidgetDirection LayoutDirection
		{
			get { return GetLayoutDirection(); }
			set { SetLayoutDirection(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern WidgetModel GetLayoutModel();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetLayoutModel(WidgetModel model);
		public WidgetModel LayoutModel
		{
			get { return GetLayoutModel(); }
			set { SetLayoutModel(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern WidgetJustify GetLayoutJustify();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetLayoutJustify(WidgetJustify justify);
		public WidgetJustify LayoutJustify
		{
			get { return GetLayoutJustify(); }
			set { SetLayoutJustify(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern WidgetAnchor GetLayoutAnchor();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetLayoutAnchor(WidgetAnchor anchor);
		public WidgetAnchor LayoutAnchor
		{
			get { return GetLayoutAnchor(); }
			set { SetLayoutAnchor(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern bool IsLayoutWrapping();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetLayoutWrapping(bool wrap);
		public bool LayoutWrapping
		{
			get { return IsLayoutWrapping(); }
			set { SetLayoutWrapping(value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)] private extern Bounds GetMargin();
		[MethodImpl(MethodImplOptions.InternalCall)] private extern void SetMargin(Bounds margin);
		public Bounds Margin
		{
			get { return GetMargin(); }
			set { SetMargin(value); }
		}
	}
}
