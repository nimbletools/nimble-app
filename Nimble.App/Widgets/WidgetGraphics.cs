using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Widgets
{
	public class WidgetGraphics
	{
		internal IntPtr __Ptr = IntPtr.Zero;

		[MethodImpl(MethodImplOptions.InternalCall)] public extern void Stuff();
	}
}
