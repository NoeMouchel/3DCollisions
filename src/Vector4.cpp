#include "../Include/Vector4.h"

//	Constructor -------------

ToolBox::Vector4f::Vector4f()
{
	x = y = z = w = 0.f;
}

ToolBox::Vector4f::Vector4f(float in_value)
{
	x = y = z = w = in_value;
}

ToolBox::Vector4f::Vector4f(float in_x, float in_y, float in_z)
{
	x = in_x;
	y = in_y;
	z = in_z;
	w = 1.f;
};

ToolBox::Vector4f::Vector4f(float in_x, float in_y, float in_z, float in_w)
{
	x = in_x;
	y = in_y;
	z = in_z;
	w = in_w;
};

ToolBox::Vector4f::Vector4f(const Vector4f& in_U, const Vector4f& in_V)
{
	x = in_V.x - in_U.x;
	y = in_V.y - in_U.y;
	z = in_V.z - in_U.z;
	w = in_V.w - in_U.w;
}
