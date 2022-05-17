#pragma once

#include "../Include/Intersection3.h"

#include "../Include/Transform3.h"
#include "../Include/Quaternion.h"


#define EARTH_GRAVITY 9.81f

namespace ToolBox
{
	class RigidBody3
	{
	public:
		//	Constructor
		//	-----------
		RigidBody3();
		RigidBody3(Transform3* in_transform);

		//	Variables
		//	---------
		Transform3* m_transform;
		Vector3f  m_velocity;
		Vector3f  m_acceleration = { 0.f, -EARTH_GRAVITY, 0.f };
		Vector3f  m_next_pos;

		float m_mass = 1.f;
		bool  m_isGravity = true;

		float m_Em0;
		float m_Em;
		float m_Ec;
		float m_Ep;


		//	Functions
		//	---------

		//	Apply gravity to the velocity 
		//  Parameters : float deltaTime
		//	----------------------------
		void applyEnergy(float deltaTime);

		void getEnergies();
		//void getReboundVelocity();

		//	Update the rigidbody 
		//  Parameters : float deltaTime
		//	----------------------------
		void update(float deltaTime);

		//	Precalculate the next frame position
		//	Parameters : float deltaTime
		//	----------------------------
		void preCalculateNextPos(float deltaTime);
	};
}