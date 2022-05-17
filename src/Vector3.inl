
using namespace ToolBox;


inline Vector3f    ToolBox::operator-(const Vector3f& a, const Vector3f& b)
{ 
	return { a.x - b.x, a.y - b.y, a.z - b.z }; 
}

inline Vector3f    ToolBox::operator+(const Vector3f& a, const Vector3f& b)
{ 
	return { a.x + b.x, a.y + b.y, a.z + b.z }; 
}

inline Vector3f ToolBox::operator-(const Vector3f& a)
{
	return { -a.x, -a.y, -a.z };
}


inline Vector3f    ToolBox::operator+(const Vector3f& a, const float value)
{
	return { a.x + value, a.y + value, a.z + value };
}

inline Vector3f    ToolBox::operator-(const Vector3f& a, const float value)
{
	return { a.x - value, a.y - value, a.z - value };
}

inline Vector3f    ToolBox::operator*(const Vector3f& a, const float scale)
{
	return { a.x * scale, a.y * scale, a.z * scale };
}

inline Vector3f    ToolBox::operator/(const Vector3f& a, const float value)
{
	return { a.x / value, a.y / value, a.z / value };
}



inline Vector3f    ToolBox::operator+(const float value, const Vector3f& a)
{
	return a + value;
}

inline Vector3f    ToolBox::operator*(const float value, const Vector3f& a)
{
	return a * value;
}


inline bool    ToolBox::operator==(const Vector3f& a, const Vector3f& b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
inline bool    ToolBox::operator!=(const Vector3f& a, const Vector3f& b)
{
	return !(a == b);
}


inline Vector3f ToolBox::vector3CrossProduct(const Vector3f& a, const Vector3f& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}


inline Vector3f	ToolBox::xVector3(const float x)
{
	return { x,0.f,0.f };
};


inline Vector3f	ToolBox::yVector3(const float y)
{
	return { 0.f,y,0.f };
};


inline Vector3f ToolBox::zVector3(const float z)
{
	return { 0.f,0.f,z };
};


inline Vector3f	ToolBox::vector3Zero()
{
	return { 0.f ,0.f ,0.f };
}


inline Vector3f ToolBox::vector3Reflect(const Vector3f& in, const Vector3f& normal)
{
	return in - normal * (2 * (dotProduct(in, normal)));
}


inline Vector3f	ToolBox::vector3Orthogonal(const Vector3f& v)
{
	float x = abs(v.x);
	float y = abs(v.y);
	float z = abs(v.z);

	Vector3f other = x < y ? (x < z ? X_AXIS_VEC3 : Z_AXIS_VEC3) : (y < z ? Y_AXIS_VEC3 : Z_AXIS_VEC3);
	return vector3CrossProduct(v, other);
}

inline Vector3f ToolBox::getVector3Perpendicular(const Vector3f& v, const Vector3f& axis)
{
	return v - getVector3Projection(v, axis);
}

inline Vector3f ToolBox::getVector3Projection(const float dot, const Vector3f& axis)
{
	return dot / axis.squareLength() * axis;
}

inline Vector3f ToolBox::getVector3Projection(const Vector3f& v, const Vector3f& axis)
{
	return getVector3Projection(dotProduct(v, axis), axis);
}