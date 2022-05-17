
/*========================    Vector 4    ========================*/

//	----- Operators Vector 4 - Vector 4 :

inline  ToolBox::Vector4f ToolBox::operator+(const Vector4f& a, const Vector4f& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline  ToolBox::Vector4f ToolBox::operator-(const Vector4f& a, const Vector4f& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

inline ToolBox::Vector4f ToolBox::operator*(const Vector4f& a, const Vector4f& b)
{
	return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

inline  ToolBox::Vector4f	 ToolBox::operator/(const Vector4f& a, const Vector4f& b)
{
	return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
}


inline  ToolBox::Vector4f	 ToolBox::operator-(const Vector4f& a)
{
	return { -a.x, -a.y, -a.z , -a.w };
}
//	----- Operators Vector 4 - float:

inline  ToolBox::Vector4f	 ToolBox::operator+(const Vector4f& a, const float b)
{
	return { a.x + b, a.y + b, a.z + b, a.w + b };
}

inline  ToolBox::Vector4f	 ToolBox::operator-(const Vector4f& a, const float b)
{
	return { a.x - b, a.y - b, a.z - b, a.w - b };
}

inline  ToolBox::Vector4f	 ToolBox::operator*(const Vector4f& a, const float b)
{
	return { a.x * b, a.y * b, a.z * b, a.w * b };
}

inline  ToolBox::Vector4f	 ToolBox::operator/(const Vector4f& a, const float b)
{
	return { a.x / b, a.y / b, a.z / b, a.w / b };
}