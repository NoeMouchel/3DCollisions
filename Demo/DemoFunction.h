#pragma once
#include <raylib.h>
#include "../Include/Matrix.h"

using namespace ToolBox;

//	Conversion functions to Raylib\
//	------------------------------
Matrix		Mat4x4_to_Matrix(const Mat4x4& mat);
Vector3		Vector3f_to_Vector3(const Vector3f& vec3);
Vector3f	Vector3_to_Vector3f(const Vector3& vec3);


