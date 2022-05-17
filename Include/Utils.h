#pragma once

#include "../src/Utils.inl"

#ifndef PI
#define PI		3.14159265358
#endif

#ifndef HALF_PI
#define HALF_PI 1.57079632679
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG 57.2958f
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD 0.0174533f
#endif

namespace ToolBox
{
	//	Return minimum value between two values
	//	Parameters : Type a, Type b
	//	---------------------------
	template<typename T>
	T min(T a, T b);

	//	Return maximum value between two values
	//	Parameters : Type a, Type b
	//	---------------------------
	template<typename T>
	T max(T a, T b);

	//	Return a clamped value between two values
	//	Parameters : Type value, Type min, Type max
	//	-------------------------------------------
	template<typename T>
	T clamp(T value, T min, T max);

	//	Return a looped value between two values
	//	Parameters : Type value, Type min, Type max
	//	-------------------------------------------
	template<typename T>
	T loop(T value, T min, T max);

	//	Return a mapped value between two values
	//	Parameters : Type value, Type min1, Type max1, Type min2, Type max2
	//	-------------------------------------------------------------------
	template<typename T>
	T map(T value, T min1, T max1, T min2, T max2);

	//	Switch boolean to its inverse
	//	Parameters : bool& a
	//	--------------------
	void switchBoolean(bool& a);
}

