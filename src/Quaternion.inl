#include <cmath>

using namespace ToolBox;
/*========================    Quaternion    ========================*/


inline ToolBox::Quaternion ToolBox::quaternionIdentity()
{
	return { 0.0f, 0.0f, 0.0f, 1.0f };
}


inline ToolBox::Quaternion ToolBox::operator+(const Quaternion& q1, const Quaternion& q2)
{
	return { q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w };
}


inline ToolBox::Quaternion ToolBox::operator+(const Quaternion& q, float value)
{
	return { q.x + value, q.y + value, q.z + value, q.w + value };
}




inline ToolBox::Quaternion ToolBox::operator-(const Quaternion& q1, const Quaternion& q2)
{
    return { q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w };
}

inline ToolBox::Quaternion ToolBox::operator-(const Quaternion& q, float value)
{
	return { q.x - value, q.y - value, q.z - value, q.w - value };
}




inline ToolBox::Quaternion ToolBox::operator*(const Quaternion& q1, const Quaternion& q2)
{
    return 
    {
        q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y,
        q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z,
        q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
    };
}


inline ToolBox::Quaternion ToolBox::operator*(const Quaternion& q, float value)
{
    return 
    {
        q.x * value + q.w * value + q.y * value - q.z * value,
        q.y * value + q.w * value + q.z * value - q.x * value,
        q.z * value + q.w * value + q.x * value - q.y * value,
        q.w * value - q.x * value - q.y * value - q.z * value
    };
}


inline ToolBox::Quaternion ToolBox::operator/(const Quaternion& q1, const Quaternion& q2)
{
    return { q1.x / q2.x, q1.y / q2.y, q1.z / q2.z, q1.w / q2.w };
}



inline ToolBox::Quaternion ToolBox::quaternionLerp(Quaternion q1, Quaternion q2, float amount)
{
    return
    {
        q1.x + amount * (q2.x - q1.x),
        q1.y + amount * (q2.y - q1.y),
        q1.z + amount * (q2.z - q1.z),
        q1.w + amount * (q2.w - q1.w)
    };
}

inline ToolBox::Quaternion ToolBox::quaternionNormalizedlerp(Quaternion q1, Quaternion q2, float amount)
{
    return quaternionLerp(q1, q2, amount).normalized();
}
