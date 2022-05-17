#include "../Include/Collider3.h"
#include "../Include/Intersection3.h"

//using namespace ToolBox;

SphereCollider::SphereCollider(const Transform3* in_transform, const float in_radius)
{
	m_transform = in_transform;
	m_radius = in_radius;
}

void ToolBox::SphereCollider::checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime)
{
	Vector3f back_point = rb.m_transform->m_position - rb.m_velocity.normalized() * (radius + m_radius);
	Vector3f next_pos   = rb.m_transform->m_position + rb.m_velocity * deltaTime;
	Hit out;

	if (intersection_segment_sphere(back_point, next_pos, Sphere(m_transform->m_position, m_radius + radius), out))
	{
		//	Get Moving Object center to intersection point
		Vector3f AI = (out.point - rb.m_transform->m_position);

		//	Distance between Intersection point and the old next pos
		float distanceIB = getDistance(next_pos, out.point);

		//	New direction
		Vector3f new_dir = vector3Reflect(AI, out.normal).normalized();

		//	New position (old one, because we need to recheck if there are near collision, before updating new pos)
		rb.m_next_pos = rb.m_transform->m_position;

		//	New Velocity (without force loss for now)
		rb.m_velocity = new_dir * rb.m_velocity.length();
	}
}

void ToolBox::SphereCollider::checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N)
{
	Hit out;
	intersection_segment_sphere(A, B, Sphere(m_transform->m_position, m_radius), out);
	I = out.point;
	N = out.normal;
}


RoundedBoxCollider::RoundedBoxCollider(const Transform3* in_transform, const float in_radius)
{
	m_transform = in_transform;
	m_radius = in_radius;
}

void ToolBox::RoundedBoxCollider::checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime)
{
	Vector3f back_point = rb.m_transform->m_position - rb.m_velocity.normalized() *( radius + m_radius);
	Vector3f next_pos   = rb.m_transform->m_position + rb.m_velocity * deltaTime;

	float speed = rb.m_velocity.length();
	Hit out;

	RoundedBox BoxCollision(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale + radius, m_radius + radius);

	if (intersection_segment_roundedbox(back_point, next_pos, BoxCollision, out))
	{
		//	Get Moving Object center to intersection point
		Vector3f AI = (out.point - rb.m_transform->m_position);

		//	Distance between Intersection point and the old next pos
		float distanceIB = getDistance(next_pos, out.point);

		//	New direction
		Vector3f new_dir =  vector3Reflect(AI, out.normal).normalized();

		//	New position ( old one, because we need to recheck if there are near collision, before updating new pos)
		rb.m_next_pos = rb.m_transform->m_position;

		//	New Velocity (without force loss for now)
		rb.m_velocity = new_dir * rb.m_velocity.length();
	}
}

void ToolBox::RoundedBoxCollider::checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N)
{
	Hit out;
	intersection_segment_roundedbox(A, B, RoundedBox(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale, m_radius), out);
	I = out.point;
	N = out.normal;
}


BoxCollider::BoxCollider(const Transform3* in_transform)
{
	m_transform = in_transform;
}

void ToolBox::BoxCollider::checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime)
{
	Vector3f back_point = rb.m_transform->m_position - rb.m_velocity.normalized() * radius;
	Vector3f next_pos   = rb.m_transform->m_position + rb.m_velocity * deltaTime;
	Hit out;


	RoundedBox collisionBox(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale + radius, radius);

	if (intersection_segment_roundedbox(back_point, next_pos, collisionBox, out))
	{
		//	Get Moving Object center to intersection point
		Vector3f AI = (out.point - rb.m_transform->m_position);

		//	Distance between Intersection point and the old next pos
		float distanceIB = getDistance(next_pos, out.point);

		//	New direction
		Vector3f new_dir = vector3Reflect(AI, out.normal).normalized();

		//	New position ( old one, because we need to recheck if there are near collision, before updating new pos)
		rb.m_next_pos = rb.m_transform->m_position;

		//	New Velocity (without force loss for now)
		rb.m_velocity = new_dir * rb.m_velocity.length();
	}
}

void ToolBox::BoxCollider::checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N)
{
	Hit out;
	intersection_segment_box(A, B, Box(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale), out);
	I = out.point;
	N = out.normal;
}


CapsuleCollider::CapsuleCollider(const Transform3* in_transform, const float in_height, const float in_radius)
{
	m_transform = in_transform;
	m_height = in_height;
	m_radius = in_radius;
}

void ToolBox::CapsuleCollider::checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime)
{
	Vector3f back_point = rb.m_transform->m_position - rb.m_velocity.normalized() * radius;
	Vector3f next_pos   = rb.m_transform->m_position + rb.m_velocity * deltaTime;
	float speed = rb.m_velocity.length();
	Hit out;

	if (intersection_segment_capsule(back_point, next_pos, Capsule(m_transform->m_position, m_transform->m_rotation, m_height, radius), out))
	{
		//	Get Moving Object center to intersection point
		Vector3f AI = (out.point - rb.m_transform->m_position);

		//	Distance between Intersection point and the old next pos
		float distanceIB = getDistance(next_pos, out.point);

		//	New direction
		Vector3f new_dir = vector3Reflect(AI, out.normal).normalized();

		//	New position ( old one, because we need to recheck if there are near collision, before updating new pos)
		rb.m_next_pos = rb.m_transform->m_position;

		//	New Velocity (without force loss for now)
		rb.m_velocity = new_dir * rb.m_velocity.length();
	}
}

void ToolBox::CapsuleCollider::checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N)
{
	Hit out;
	intersection_segment_capsule(A, B, Capsule(m_transform->m_position, m_transform->m_rotation, m_height, m_transform->m_scale.x), out);
	I = out.point;
	N = out.normal;
}