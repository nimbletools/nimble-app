using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Bounds
	{
		public int Left;
		public int Right;
		public int Top;
		public int Bottom;

		public Bounds(int all)
		{
			Left = Right = Top = Bottom = all;
		}

		public Bounds(int horizontal, int vertical)
		{
			Left = Right = horizontal;
			Top = Bottom = vertical;
		}

		public Bounds(int left, int right, int top, int bottom)
		{
			Left = left;
			Right = right;
			Top = top;
			Bottom = bottom;
		}
	}
}
