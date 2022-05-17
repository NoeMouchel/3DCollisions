#pragma once
#include "../Include/Quaternion.h"
#include "../Include/Vector3.h"

namespace ToolBox
{
	//	Transform class, contain position, rotation and scale of an object
	//	------------------------------------------------------------------

	class Transform3
	{
	public:
		//	Constructor
		//	-----------
		Transform3() = default;
		Transform3(const Vector3f& in_position, const Quaternion& in_rotation, const Vector3f& in_scale);

		//	Variables
		//	---------
		Vector3f	m_position;
		Quaternion	m_rotation;
		Vector3f	m_scale;
	};
}