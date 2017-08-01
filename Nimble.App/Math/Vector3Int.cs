using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector3Int
	{
		public int X, Y, Z;

		public Vector3Int(int s)
		{
			X = Y = Z = s;
		}

		public Vector3Int(int x, int y, int z)
		{
			X = x;
			Y = y;
			Z = z;
		}
	}
}
