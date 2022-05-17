#include "../Include/RigidBody3.h"
#include "../Include/Utils.h"

using namespace ToolBox;



RigidBody3::RigidBody3()
{
	m_velocity = { 0.f, -sqrtf(2.f), 0.f };
	getEnergies();
	m_Em0 = m_Em;

}

RigidBody3::RigidBody3(Transform3* in_transform)
{
	m_transform = in_transform;

	m_velocity = { 0.f, -1.f, 0.f };
	getEnergies();
	m_Em0 = m_Em;
}




void RigidBody3::getEnergies()
{
	m_Ec = (m_mass * m_velocity.squareLength()) * .5f;
	m_Ep = m_mass * EARTH_GRAVITY * m_transform->m_position.y;

	m_Em = m_Ec + m_Ep;
}

void RigidBody3::applyEnergy(float deltaTime)
{
	getEnergies();
	m_velocity = m_velocity.normalized() * sqrtf(ToolBox::max(0.f, 2.f * (m_Em0 - m_Ep) / m_mass)) + m_acceleration * deltaTime;
}

void RigidBody3::update(float deltaTime)
{
	//	If gravity is enabled apply it
	if(m_isGravity == true)
		applyEnergy(deltaTime);
}


void RigidBody3::preCalculateNextPos(float deltaTime)
{
	m_next_pos = m_transform->m_position + m_velocity * deltaTime;
}
