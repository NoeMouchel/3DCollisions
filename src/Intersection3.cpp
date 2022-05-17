#include "../Include/Intersection3.h"
#include "../Include/Utils.h"

#define INTERSECTION	true
#define NO_INTERSECTION	false



bool ToolBox::intersection_segment_plane(const Vector3f& ptA, const Vector3f& ptB,const Plane& in_plane, Hit& out_hit)
{
	Vector3f vect_AB = ptB - ptA;
	float dot_AB_n	 = dotProduct(vect_AB, in_plane.m_normal);

	//	If AB and the plane normal are orthogonal, it means that the plane and AB are colinear
	//	So there is no intersections
	if (abs(dot_AB_n) < EPSILON)
	{
		return NO_INTERSECTION;
	}

	//	Dot product of AP  (P is the nearest plane point from the origin) and the plane normal
	float dot_AP_n = dotProduct(in_plane.m_normal * in_plane.m_distance - ptA, in_plane.m_normal);

	float t = dot_AP_n / dot_AB_n;

	//	Because it is a segment if AP.n and AB.n have different sign, or if AP.n is superior to AB.n,
	//	[AB] can't intersect with the plane
	if (t < 0 || t > 1)
	{
		return NO_INTERSECTION;
	}

	//	t allow us to obtain the position of the intersection point on the segment AB
	out_hit.point	= ptA + vect_AB * t;
	out_hit .normal = in_plane.m_normal;

	return INTERSECTION;
}


bool ToolBox::intersection_line_plane(const Vector3f& ptA, const Vector3f& ptB, const  Plane& in_plane, Hit& out_hit)
{
	Vector3f vect_AB = ptB - ptA;
	float dot_AB_n	 = dotProduct(vect_AB, in_plane.m_normal);

	//	If AB and the plane normal are orthogonal, it means that the plane and AB are colinear
	//	So there is no intersections
	if (abs(dot_AB_n) < EPSILON)
	{
		return NO_INTERSECTION;
	}

	//	Else, because it is a line and a plane with infinite length, there is an intersection for sure

	float dot_AP_n = dotProduct(in_plane.m_normal * in_plane.m_distance - ptA, in_plane.m_normal);

	float t = dot_AP_n / dot_AB_n;

	//	t allow us to obtain the position of the intersection point on the line AB
	out_hit.point  = ptA + vect_AB * t;
	out_hit.normal = in_plane.m_normal;

	return INTERSECTION;
}



bool ToolBox::intersection_segment_disk(const Vector3f& ptA, const Vector3f& ptB, const Disk& in_disk, Hit& out_hit)
{
	if (!intersection_segment_plane(ptA, ptB, Plane(in_disk), out_hit))
	{
		return NO_INTERSECTION;
	}

	Vector3f _PI = out_hit.point - in_disk.m_center;

	if (_PI.squareLength() <= in_disk.m_radius * in_disk.m_radius)
	{
		return INTERSECTION;
	}

	return NO_INTERSECTION;
}

bool ToolBox::intersection_segment_sphere(const Vector3f& ptA, const Vector3f& ptB, const Sphere& in_sphere, Hit& out_hit)
{
	if (ptB == ptA) return NO_INTERSECTION;

	//	Here, O is the sphere center

	Vector3f AB = ptB - ptA;
	Vector3f OA = ptA - in_sphere.m_center;

	//	Second degree polynomial to find t
	float a = AB.squareLength();;
	float b = 2.f * dotProduct(OA, AB);
	float c = OA.squareLength() - (in_sphere.m_radius * in_sphere.m_radius);
	float delta = (b * b) - (4 * a * c);

	if (delta < 0.f) return NO_INTERSECTION;
	

	float t = -(b + sqrt(delta)) / (2 * a);

	if (t < 0 || t > 1)
	{
		return NO_INTERSECTION;
	}

	//	t allow us to obtain the position of the intersection point on the segment AB
	out_hit.point  = ptA + AB * t;
	out_hit.normal = (out_hit.point - in_sphere.m_center).normalized();

	return INTERSECTION;
}

bool ToolBox::intersection_segment_inf_cylinder(const Vector3f& ptA, const Vector3f& ptB, const Cylinder& in_cyl, Hit& out_hit)
{
	if (in_cyl.m_height == 0.f) return NO_INTERSECTION;

	Vector3f ptP = in_cyl.m_center - vector3RotateByQuaternion({ 0,in_cyl.m_height * .5f,0 }, in_cyl.m_rotation);
	Vector3f ptQ = in_cyl.m_center + vector3RotateByQuaternion({ 0,in_cyl.m_height * .5f,0 }, in_cyl.m_rotation);
	Vector3f AB = ptB - ptA;
	Vector3f PQ = ptQ - ptP;
	Vector3f PA = ptA - ptP;

	float dot_AB_PQ = dotProduct(AB, PQ);
	float dot_PA_PQ = dotProduct(PA, PQ);
	float dot_PA_AB = dotProduct(PA, AB);

	float dot_AB_AB = dotProduct(AB, AB);
	float dot_PQ_PQ = dotProduct(PQ, PQ);
	float dot_PA_PA = dotProduct(PA, PA);

	float a = dot_PQ_PQ * dot_AB_AB - dot_AB_PQ * dot_AB_PQ;
	float b = 2 * (dot_PQ_PQ * dot_PA_AB - dot_AB_PQ * dot_PA_PQ);
	float c = dot_PQ_PQ * (dot_PA_PA - in_cyl.m_radius * in_cyl.m_radius) - dot_PA_PQ * dot_PA_PQ;

	float delta = (b * b) - (4 * a * c);

	if (delta < 0.f) return NO_INTERSECTION;
	
	float t = -(b + sqrt(delta)) / (2 * a);

	if (t > 1 || t < 0)
	{
		return NO_INTERSECTION;
	}

	//	t allow us to obtain the position of the intersection point on the segment AB
	out_hit.point = ptA + AB * t;
	

	return INTERSECTION;
}

bool ToolBox::intersection_segment_cylinder(const Vector3f& ptA, const Vector3f& ptB, const Cylinder& in_cyl, Hit& out_hit)
{

	if (in_cyl.m_height == 0.f) return NO_INTERSECTION;

	Vector3f ptP = in_cyl.m_center - vector3RotateByQuaternion({ 0,in_cyl.m_height * .5f,0 }, in_cyl.m_rotation);
	Vector3f ptQ = in_cyl.m_center + vector3RotateByQuaternion({ 0,in_cyl.m_height * .5f,0 }, in_cyl.m_rotation);

	Vector3f AB = ptB - ptA;
	Vector3f PQ = ptQ - ptP;
	Vector3f PA = ptA - ptP;

	float dot_AB_PQ = dotProduct(AB, PQ);
	float dot_PA_PQ = dotProduct(PA, PQ);
	float dot_PA_AB = dotProduct(PA, AB);

	float dot_AB_AB = dotProduct(AB, AB);
	float dot_PQ_PQ = dotProduct(PQ, PQ);
	float dot_PA_PA = dotProduct(PA, PA);

	float a = dot_PQ_PQ * dot_AB_AB - dot_AB_PQ * dot_AB_PQ;
	float c = dot_PQ_PQ * (dot_PA_PA - in_cyl.m_radius * in_cyl.m_radius) - dot_PA_PQ * dot_PA_PQ;

	if (abs(a) < EPSILON && c > 0.f) return NO_INTERSECTION;

	//	If c < 0, it means that there is no collision on the rounded faces, so let's check the disks on the top/bottom 
	if (c < 0.f)
	{
		if (dot_PA_PQ < 0.f)
		{
			return intersection_segment_disk(ptA, ptB, Disk(-PQ.normalized(), ptP, in_cyl.m_radius), out_hit);
		}

		if (dot_PA_PQ > dot_PQ_PQ)
		{
			return intersection_segment_disk(ptA, ptB, Disk(PQ.normalized(), ptQ, in_cyl.m_radius), out_hit);
		}

		return NO_INTERSECTION;
	}

	float b = (dot_PQ_PQ * dot_PA_AB - dot_AB_PQ * dot_PA_PQ);
	float delta = (b * b) - (a * c);

	if (delta < 0.f) return NO_INTERSECTION;

	if (delta > 0.f)
	{
		float t = -(b + sqrt(delta)) / a;

		if (t > 1 || t < 0)
		{
			return NO_INTERSECTION;
		}

		out_hit.point = ptA + AB * t;
	}

	float dot_PI_PQ = dotProduct(out_hit.point - ptP, PQ);

	if (dot_PI_PQ < 0)
	{
		return intersection_segment_disk(ptA, ptB, Disk(-PQ.normalized(), ptP, in_cyl.m_radius), out_hit);

	}

	if (dot_PI_PQ > dot_PQ_PQ)
	{
		return intersection_segment_disk(ptA, ptB, Disk(PQ.normalized(), ptQ, in_cyl.m_radius), out_hit);
	}
	out_hit.normal = getVector3Perpendicular(out_hit.point - ptP, PQ).normalized();

	return INTERSECTION;
}



bool ToolBox::intersection_segment_capsule(const Vector3f& ptA, const Vector3f& ptB, const Capsule& in_cap, Hit& out_hit)
{
	Vector3f ptP = in_cap.m_center - vector3RotateByQuaternion({ 0,in_cap.m_height * .5f,0 }, in_cap.m_rotation);
	Vector3f ptQ = in_cap.m_center + vector3RotateByQuaternion({ 0,in_cap.m_height * .5f,0 }, in_cap.m_rotation);

	Vector3f AB = ptB - ptA;
	Vector3f PQ = ptQ - ptP;
	Vector3f PA = ptA - ptP;

	float dot_AB_PQ = dotProduct(AB, PQ);
	float dot_PA_PQ = dotProduct(PA, PQ);
	float dot_PA_AB = dotProduct(PA, AB);

	float dot_AB_AB = dotProduct(AB, AB);
	float dot_PQ_PQ = dotProduct(PQ, PQ);
	float dot_PA_PA = dotProduct(PA, PA);

	float a = dot_PQ_PQ * dot_AB_AB - dot_AB_PQ * dot_AB_PQ;
	float c = dot_PQ_PQ * (dot_PA_PA - in_cap.m_radius * in_cap.m_radius) - dot_PA_PQ * dot_PA_PQ;

	if ((a > -EPSILON && a < EPSILON) && c > 0.f) return NO_INTERSECTION;


	if (c < 0.f)
	{
		if (dot_PA_PQ < 0.f)
		{
			return intersection_segment_sphere(ptA, ptB, Sphere(ptP, in_cap.m_radius), out_hit);
		}

		if (dot_PA_PQ > dot_PQ_PQ)
		{
			return intersection_segment_sphere(ptA, ptB, Sphere(ptQ, in_cap.m_radius), out_hit);
		}

		return NO_INTERSECTION;
	}

	float b = (dot_PQ_PQ * dot_PA_AB - dot_AB_PQ * dot_PA_PQ);
	float delta = (b * b) - (a * c);

	if (delta < 0.f)
	{
		return NO_INTERSECTION;
	}

	else if (delta > 0.f)
	{
		float t = -(b + sqrt(delta)) / a;

		if (t > 1 || t < 0)
		{
			return NO_INTERSECTION;
		}

		out_hit.point = ptA + AB * t;
	}

	float dot_PI_PQ = dotProduct(out_hit.point - ptP, PQ);

	if (dot_PI_PQ < 0)
	{
		return intersection_segment_sphere(ptA, ptB, Sphere(ptP, in_cap.m_radius), out_hit);
	}

	if (dot_PI_PQ > dot_PQ_PQ)
	{
		return intersection_segment_sphere(ptA, ptB, Sphere(ptQ, in_cap.m_radius), out_hit);
	}
	out_hit.normal = getVector3Perpendicular(out_hit.point - ptP, PQ).normalized();

	return INTERSECTION;
}


bool ToolBox::intersection_segment_quad(const Vector3f& ptA, const Vector3f& ptB, const Quad& in_quad, Hit& out_hit)
{
	if (in_quad.m_extension.x == 0.f || in_quad.m_extension.y == 0.f)	 return NO_INTERSECTION;
	if (intersection_segment_plane(ptA, ptB, in_quad, out_hit) == false) return NO_INTERSECTION;

	Vector3f OI = (out_hit.point - in_quad.m_center);
	Vector3f x  = vector3RotateByQuaternion(Vector3f(1.f, 0.f, 0.f), in_quad.m_rotation);
	Vector3f y  = vector3RotateByQuaternion(Vector3f(0.f, 0.f, 1.f), in_quad.m_rotation);

	if (abs(dotProduct(OI, x)) > in_quad.m_extension.x || abs(dotProduct(OI, y)) > in_quad.m_extension.y) return NO_INTERSECTION;

	return INTERSECTION;
}


void CheckNearestIntersection(Hit& out_hit, const Vector3f& ptA, const Hit& in_hit, bool& intersected)
{
	if (intersected == NO_INTERSECTION)
	{
		out_hit.point = in_hit.point;
		out_hit.normal = in_hit.normal;
	}
	else if ((out_hit.point - ptA).squareLength() < (out_hit.point - ptA).squareLength())
	{
		out_hit.point = in_hit.point;
		out_hit.normal = in_hit.normal;
	}

	intersected = INTERSECTION;
}

bool ToolBox::intersection_segment_box(const Vector3f& ptA, const Vector3f& ptB, const Box& in_box, Hit& out_hit)
{
	Vector3f i = vector3RotateByQuaternion({ 1.f,0.f,0.f }, in_box.m_rotation);
	Vector3f j = vector3RotateByQuaternion({ 0.f,1.f,0.f }, in_box.m_rotation);
	Vector3f k = vector3RotateByQuaternion({ 0.f,0.f,1.f }, in_box.m_rotation);
	Vector3f AB = Vector3f(ptA, ptB);

	//	Upper face intersection check
	if (dotProduct(j, AB) < 0.f)
	{
		Quad upperFace = Quad(in_box.m_center + j * in_box.m_extension.y, in_box.m_rotation, Vector2f(in_box.m_extension.x, in_box.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, upperFace, out_hit))
		{
			return  INTERSECTION;
		}
	}
	//	Bottom face intersection check
	else
	{
		Quad bottomFace = Quad(in_box.m_center - j * in_box.m_extension.y, in_box.m_rotation * quaternionFromEuler(zVector3((float)PI)), Vector2f(in_box.m_extension.x, in_box.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, bottomFace, out_hit))
		{
			return  INTERSECTION;
		}
	}

	//	Right face intersection check
	if (dotProduct(i, AB) < 0.f)
	{
		Quad rightFace = Quad(in_box.m_center + i * in_box.m_extension.x, in_box.m_rotation * quaternionFromEuler(zVector3(-(float)HALF_PI)), Vector2f(in_box.m_extension.y, in_box.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, rightFace, out_hit))
		{
			return  INTERSECTION;
		}
	}
	//	Left face intersection check
	else
	{
		Quad leftFace = Quad(in_box.m_center - i * in_box.m_extension.x, in_box.m_rotation * quaternionFromEuler(zVector3((float)HALF_PI)), Vector2f(in_box.m_extension.y, in_box.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, leftFace, out_hit))
		{
			return  INTERSECTION;
		}
	}

	//	Front face intersection check
	if (dotProduct(k, AB) < 0.f)
	{

		Quad frontFace = Quad(in_box.m_center + k * in_box.m_extension.z, in_box.m_rotation * quaternionFromEuler(xVector3((float)HALF_PI)), Vector2f(in_box.m_extension.x, in_box.m_extension.y));

		if (intersection_segment_quad(ptA, ptB, frontFace, out_hit))
		{
			return  INTERSECTION;
		}
	}
	//	Back face intersection check
	else
	{
		Quad backFace = Quad(in_box.m_center - k * in_box.m_extension.z, in_box.m_rotation * quaternionFromEuler(xVector3(-(float)HALF_PI)), Vector2f(in_box.m_extension.x, in_box.m_extension.y));

		if (intersection_segment_quad(ptA, ptB, backFace, out_hit))
		{
			return  INTERSECTION;
		}
	}

	return NO_INTERSECTION;
}



bool intersect_segment_voronol_region(const Vector3f& ptA, const Vector3f& ptB, const Quad& in_quad, const float in_radius, Hit& out_hit)
{

	float radius;
	radius = ToolBox::min(in_quad.m_extension.x, in_radius);
	radius = ToolBox::min(in_quad.m_extension.y, in_radius);

	Quad shortQuad = Quad(in_quad.m_center, in_quad.m_rotation, in_quad.m_extension - radius);
	if (intersection_segment_quad(ptA, ptB, shortQuad, out_hit)) return INTERSECTION;

	Vector3f i = vector3RotateByQuaternion({ 1.f,0.f,0.f }, in_quad.m_rotation);
	Vector3f j = vector3RotateByQuaternion({ 0.f,1.f,0.f }, in_quad.m_rotation);
	Vector3f k = vector3RotateByQuaternion({ 0.f,0.f,1.f }, in_quad.m_rotation);

	Capsule cap;
	Vector3f OI = out_hit.point - in_quad.m_center;
	float dot_I_OI = dotProduct(i, OI);
	float dot_K_OI = dotProduct(k, OI);

	if (fabsf(dot_I_OI) > fabsf(dot_K_OI))
	{
		//	Is a vertical capsule

		//	Left or Right?
		float sign = dot_I_OI > 0.f ? 1.f : -1.f;
		cap = Capsule(in_quad.m_center - j * radius + sign * i * shortQuad.m_extension.x, shortQuad.m_rotation * quaternionFromEuler(xVector3((float)HALF_PI)), shortQuad.m_extension.y * 2.f, radius);
	}
	else
	{
		//	Is an horizontal capsule

		//	Bottom/back or up/front?
		float sign = dot_K_OI > 0.f ? 1.f : -1.f;
		cap = Capsule(shortQuad.m_center - j * radius + sign * k * shortQuad.m_extension.y, shortQuad.m_rotation * quaternionFromEuler(zVector3((float)HALF_PI)), shortQuad.m_extension.x * 2.f, radius);
	}

	if (intersection_segment_capsule(ptA, ptB, cap, out_hit)) return INTERSECTION;

	return NO_INTERSECTION;
}


bool ToolBox::intersection_segment_roundedbox(const Vector3f& ptA, const Vector3f& ptB, const RoundedBox& in_rbox, Hit& out_hit)
{
	Vector3f i = vector3RotateByQuaternion({ 1.f,0.f,0.f }, in_rbox.m_rotation);
	Vector3f j = vector3RotateByQuaternion({ 0.f,1.f,0.f }, in_rbox.m_rotation);
	Vector3f k = vector3RotateByQuaternion({ 0.f,0.f,1.f }, in_rbox.m_rotation);
	Vector3f AB = Vector3f(ptA, ptB);

	//	Upper face intersection check
	if (dotProduct(j, AB) < 0.f)
	{
		Quad upperFace =  Quad(in_rbox.m_center + j * in_rbox.m_extension.y, in_rbox.m_rotation, Vector2f(in_rbox.m_extension.x, in_rbox.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, upperFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, upperFace, in_rbox.m_radius, out_hit);
		}
	}
	//	Bottom face intersection check
	else
	{
		Quad bottomFace = Quad(in_rbox.m_center - j * in_rbox.m_extension.y, in_rbox.m_rotation * quaternionFromEuler(zVector3((float)PI)), Vector2f(in_rbox.m_extension.x, in_rbox.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, bottomFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, bottomFace, in_rbox.m_radius, out_hit);
		}
	}

	//	Right face intersection check
	if (dotProduct(i, AB) < 0.f)
	{
		Quad rightFace = Quad(in_rbox.m_center + i * in_rbox.m_extension.x, in_rbox.m_rotation * quaternionFromEuler(zVector3(-(float)HALF_PI)), Vector2f(in_rbox.m_extension.y, in_rbox.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, rightFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, rightFace, in_rbox.m_radius, out_hit);
		}
	}
	//	Left face intersection check
	else
	{
		Quad leftFace = Quad(in_rbox.m_center - i * in_rbox.m_extension.x, in_rbox.m_rotation * quaternionFromEuler(zVector3((float)HALF_PI)), Vector2f(in_rbox.m_extension.y, in_rbox.m_extension.z));

		if (intersection_segment_quad(ptA, ptB, leftFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, leftFace, in_rbox.m_radius, out_hit);
		}
	}

	//	Front face intersection check
	if (dotProduct(k, AB) < 0.f)
	{

		Quad frontFace = Quad(in_rbox.m_center + k * in_rbox.m_extension.z, in_rbox.m_rotation * quaternionFromEuler(xVector3((float)HALF_PI)), Vector2f(in_rbox.m_extension.x, in_rbox.m_extension.y));

		if (intersection_segment_quad(ptA, ptB, frontFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, frontFace, in_rbox.m_radius, out_hit);
		}
	}
	//	Back face intersection check
	else
	{
		Quad backFace = Quad(in_rbox.m_center - k * in_rbox.m_extension.z, in_rbox.m_rotation * quaternionFromEuler(xVector3(-(float)HALF_PI)), Vector2f(in_rbox.m_extension.x, in_rbox.m_extension.y));

		if (intersection_segment_quad(ptA, ptB, backFace, out_hit))
		{
			return  intersect_segment_voronol_region(ptA, ptB, backFace, in_rbox.m_radius, out_hit);
		}
	}

	return NO_INTERSECTION;
}