using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Nimble.App.Serialization;
using Nimble.App.Math;
using System.Diagnostics;

namespace Nimble.App.Widgets
{
	[WidgetTag("vbox", "hbox")]
	public class Rect : Widget
	{
		private Vector2Int m_size;
		private Vector4 m_color;

		public Rect()
		{
			Console.WriteLine("Measuring");
			Measure();
		}

		public void Measure()
		{
			var sw = new Stopwatch();
			sw.Start();
			for (int i = 0; i < 1000; i++) {
				InvalidateLayout();
			}
			sw.Stop();
			Console.WriteLine("1000: {0}", sw.Elapsed.TotalMilliseconds);
		}

		public override void Load(ContentNode node)
		{
			base.Load(node);

			int width = node.GetInt("width", false, m_size.X);
			int height = node.GetInt("height", false, m_size.Y);
			m_size = new Vector2Int(width, height);

			m_color = node.GetColor("color", false, m_color);
		}

		public Vector2Int Size
		{
			get { return m_size; }
			set {
				if (m_size != value) {
					InvalidateLayout();
				}
				m_size = value;
			}
		}

		public Vector4 Color
		{
			get { return m_color; }
			set {
				if (m_color != value) {
					InvalidateRendering();
				}
				m_color = value;
			}
		}
	}
}
