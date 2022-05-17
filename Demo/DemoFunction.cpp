#include "DemoFunction.h"

using namespace ToolBox;

Matrix Mat4x4_to_Matrix(const Mat4x4& mat)
{
	return
	{
		mat.e[0], mat.e[4], mat.e[8], mat.e[12],
		mat.e[1], mat.e[5], mat.e[9], mat.e[13],
		mat.e[2], mat.e[6], mat.e[10], mat.e[14],
		mat.e[3], mat.e[7], mat.e[11], mat.e[15]
	};
}

Vector3 Vector3f_to_Vector3(const Vector3f& vec3)
{
	return { vec3.x, vec3.y, vec3.z };
}

Vector3f Vector3_to_Vector3f(const Vector3& vec3)
{
	return { vec3.x, vec3.y, vec3.z };
}