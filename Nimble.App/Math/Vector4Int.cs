using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector4Int
	{
		public int X, Y, Z, W;

		public Vector4Int(int s)
		{
			X = Y = Z = W = s;
		}

		public Vector4Int(int x, int y, int z, int w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}
	}
}
