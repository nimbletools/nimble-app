using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Widgets
{
	public class WidgetTagAttribute : Attribute
	{
		public string[] Tags { get; set; }

		public WidgetTagAttribute(params string[] tags)
		{
			Tags = tags;
		}
	}
}
