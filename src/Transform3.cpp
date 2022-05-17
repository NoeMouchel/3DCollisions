#include "../Include/Transform3.h"

//	Constructor of Transform3
//	Parameters : const Vector3f& in_position, const Quaternion& in_rotation, const Vector3f& in_scale
//	-------------------------------------------------------------------------------------------------
Transform3::Transform3(const Vector3f& in_position, const Quaternion& in_rotation, const Vector3f& in_scale)
{
	m_position	= in_position;
	m_rotation	= in_rotation;
	m_scale		= in_scale;
}