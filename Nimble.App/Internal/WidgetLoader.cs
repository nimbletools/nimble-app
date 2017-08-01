using Nimble.App.Widgets;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Internal
{
	internal static class WidgetLoader
	{
		internal static List<Type> WidgetTypes = new List<Type>();

		internal static void LoadWidgetTypes()
		{
			var assemblies = AppDomain.CurrentDomain.GetAssemblies();
			foreach (var asm in assemblies) {
				foreach (var type in asm.DefinedTypes) {
					if (type.IsSubclassOf(typeof(Widget))) {
						WidgetTypes.Add(type);
					}
				}
			}
		}

		internal static Type FindWidgetType(string tag)
		{
			foreach (var type in WidgetTypes) {
				if (type.FullName == tag) {
					return type;
				}

				if (type.Name.ToLower() == tag.ToLower()) {
					return type;
				}

				var tags = type.GetCustomAttribute<WidgetTagAttribute>();
				if (tags != null && tags.Tags.Contains(tag)) {
					return type;
				}
			}

			return null;
		}
	}
}
