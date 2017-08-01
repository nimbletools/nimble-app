using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector3
	{
		public float X, Y, Z;

		public Vector3(float s)
		{
			X = Y = Z = s;
		}

		public Vector3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}
	}
}
