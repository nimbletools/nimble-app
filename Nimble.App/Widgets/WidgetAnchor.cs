using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Widgets
{
	public enum WidgetAnchor
	{
		AnchorNone = 0,

		AnchorLeft = 0x020,
		AnchorRight = 0x080,
		AnchorTop = 0x040,
		AnchorBottom = 0x100,

		AnchorFillH = AnchorLeft | AnchorRight,
		AnchorFillV = AnchorTop | AnchorBottom,
		AnchorFill = AnchorLeft | AnchorRight | AnchorTop | AnchorBottom,
	}
}
