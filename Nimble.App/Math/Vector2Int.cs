using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Math
{
	public struct Vector2Int
	{
		public int X, Y;

		public Vector2Int(int s)
		{
			X = Y = s;
		}

		public Vector2Int(int x, int y)
		{
			X = x;
			Y = y;
		}

		public static bool operator ==(Vector2Int left, Vector2Int right)
		{
			return left.X == right.X && left.Y == right.Y;
		}

		public static bool operator !=(Vector2Int left, Vector2Int right)
		{
			return left.X != right.X && left.Y != right.Y;
		}
	}
}
