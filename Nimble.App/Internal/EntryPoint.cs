using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Internal
{
	internal static class EntryPoint
	{
		internal static void Initialize()
		{
			Loader.LoadAssemblies();
			WidgetLoader.LoadWidgetTypes();
		}
	}
}
