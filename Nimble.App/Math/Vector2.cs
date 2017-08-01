using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector2
	{
		public float X, Y;

		public Vector2(float s)
		{
			X = Y = s;
		}

		public Vector2(float x, float y)
		{
			X = x;
			Y = y;
		}
	}
}
