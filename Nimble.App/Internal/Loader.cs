using Nimble.App.Widgets;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Internal
{
	internal static class Loader
	{
		internal static void LoadAssemblies()
		{
			string[] paths = Directory.GetFiles(".", "*.dll");
			foreach (var path in paths) {
				if (Path.GetFileName(path) == "Nimble.App.dll") {
					continue;
				}
				if (Path.GetFileName(path) == "System.Core.dll") {
					continue;
				}

				Assembly asm = null;
				try {
					asm = Assembly.LoadFrom(path);
				} catch { continue; }

				Console.WriteLine("Loaded {0}", asm.FullName);
			}
		}
	}
}
