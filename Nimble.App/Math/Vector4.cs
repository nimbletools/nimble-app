using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector4
	{
		public float X, Y, Z, W;

		public Vector4(float s)
		{
			X = Y = Z = W = s;
		}

		public Vector4(float x, float y, float z, float w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		public static bool operator ==(Vector4 left, Vector4 right)
		{
			return
				left.X == right.X &&
				left.Y == right.Y &&
				left.Z == right.Z &&
				left.W == right.W;
		}

		public static bool operator !=(Vector4 left, Vector4 right)
		{
			return !(left == right);
		}
	}
}
