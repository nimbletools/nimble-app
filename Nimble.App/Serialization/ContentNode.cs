using Nimble.App.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Nimble.App.Serialization
{
	public class ContentNode
	{
		internal IntPtr __Ptr;

		[MethodImpl(MethodImplOptions.InternalCall)] public extern int GetInt(string name, bool required = true, int def = 0);
		[MethodImpl(MethodImplOptions.InternalCall)] public extern float GetFloat(string name, bool required = true, float def = 0.0f);
		[MethodImpl(MethodImplOptions.InternalCall)] public extern bool GetBool(string name, bool required = true, bool def = false);
		[MethodImpl(MethodImplOptions.InternalCall)] public extern string GetString(string name, bool required = true, string def = "");
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Bounds GetBounds(string name, bool required = true, Bounds def = default(Bounds));
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Vector2Int GetIvec2(string name, bool required = true, Vector2Int def = default(Vector2Int));
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Vector2 GetVec2(string name, bool required = true, Vector2 def = default(Vector2));
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Vector3 GetVec3(string name, bool required = true, Vector3 def = default(Vector3));
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Vector4 GetVec4(string name, bool required = true, Vector4 def = default(Vector4));
		[MethodImpl(MethodImplOptions.InternalCall)] public extern Vector4 GetColor(string name, bool required = true, Vector4 def = default(Vector4));

		[MethodImpl(MethodImplOptions.InternalCall)] public extern string GetContent(string def = "");
	}
}
