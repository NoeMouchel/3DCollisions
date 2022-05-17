#pragma once

#include "../Include/Shapes3.h"
#include "../Include/Rigidbody3.h"

namespace ToolBox
{
	class Collider3
	{
	public:
		//	Constructor
		//	-----------
		Collider3() = default;


		//	Variables
		//	---------
		bool	m_collided;
		const Transform3* m_transform;

		//	Functions
		//	---------
		virtual void checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime) = 0;
		virtual void checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N) = 0;
	};



	class SphereCollider : public Collider3
	{
	public:
		//	Constructor
		//	-----------
		SphereCollider() = default;
		SphereCollider(const Transform3* in_transform, const float in_radius);

		//	Variables
		//	---------
		float m_radius;

		//	Functions
		//	---------
		void checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime) override;
		void checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N) override;
	};



	class RoundedBoxCollider : public Collider3
	{
	public:
		//	Constructor
		//	-----------
		RoundedBoxCollider() = default;
		RoundedBoxCollider(const Transform3* in_transform, const float in_radius);

		//	Variables
		//	---------
		float m_radius;

		//	Functions
		//	---------
		void checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime) override;
		void checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N) override;
	};



	class BoxCollider : public Collider3
	{
	public:
		//	Constructor
		//	-----------
		BoxCollider() = default;
		BoxCollider(const Transform3* in_transform);

		//	Functions
		//	---------
		void checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime) override;
		void checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N) override;
	};



	class CapsuleCollider : public Collider3
	{
	public:
		//	Constructor
		//	-----------
		CapsuleCollider() = default;
		CapsuleCollider(const Transform3* in_transform, const float in_height, const float in_radius);

		//	Variables
		//	---------
		float m_radius;
		float m_height;

		//	Functions
		//	---------
		void checkCollisionSphere(RigidBody3& rb, const float radius, const float deltaTime) override;
		void checkSegmentIntersection(const Vector3f& A, const Vector3f& B, Vector3f& I, Vector3f& N) override;
	};
}