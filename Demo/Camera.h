#pragma once

#include <raylib.h>

class Cam
{
public:
	//	Constructor
	//	-----------
	Cam();
	
	//	Component
	//	---------
	Camera3D m_camera3D;

	//	Function
	//	--------
	void Update();
};