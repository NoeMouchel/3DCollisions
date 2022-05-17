#include <rlgl.h>

#include "SceneObject.h"
#include "DemoFunction.h"

#define INTERPLANE_SIZE .25f


void applyTransform(ToolBox::Transform3 t)
{
	rlTranslatef(t.m_position.x, t.m_position.y, t.m_position.z);
	ToolBox::Vector3f axis;
	float angle;
	t.m_rotation.toAxisAngle(axis, angle);
	rlRotatef(angle * RAD2DEG, axis.x, axis.y, axis.z);
}


//	-----------------------------


SceneObject::~SceneObject()
{
	removeRigidBody();
	removeCollider();
}

void SceneObject::update(float deltaTime)
{
	if (m_rigid_body != nullptr)
	{
		m_transform.m_position = m_rigid_body->m_next_pos;
		m_rigid_body->update(deltaTime);
	}
}

void SceneObject::addRigidBody()
{
	if (m_rigid_body != nullptr) return;

	m_rigid_body = new ToolBox::RigidBody3(&m_transform);
}

void SceneObject::removeRigidBody()
{
	if (m_rigid_body == nullptr) return;

	delete m_rigid_body;
}

void SceneObject::removeCollider()
{
	if (m_collider == nullptr) return;

	delete m_collider;
}


SphereObject::SphereObject()
{
	m_radius = .5f;
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), m_radius);
	m_type = O_SPHERE;
	m_collider = new SphereCollider(&m_transform, m_radius);
}

SphereObject::SphereObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale)
{
	m_radius = .1f;
	m_transform = Transform3(in_position, in_rotation, m_radius);
	m_type = O_SPHERE;
	m_collider = new SphereCollider(&m_transform, m_radius);
}

SphereObject::SphereObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale, float in_radius)
{
	m_radius = in_scale.x;
	m_transform = Transform3(in_position, in_rotation, m_radius);
	m_type = O_SPHERE;
	m_collider = new SphereCollider(&m_transform, m_radius);
}


void SphereObject::draw()
{
	rlPushMatrix();
		applyTransform(m_transform);
		if(m_triangle_mod)
		{
		drawSphere(m_radius, 10, 10, m_color, RL_TRIANGLES);
		}
		if (m_wireframe_mod)
		{
			drawSphere(m_radius, 10, 10, BLACK, RL_LINES);
		}
	rlPopMatrix();
}


CapsuleObject::CapsuleObject()
{
	m_radius = .1f;
	m_height = .5f;
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), m_radius);
	m_type = O_CAPSULE;
	m_collider = new CapsuleCollider(&m_transform, m_height, m_radius);
}

CapsuleObject::CapsuleObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale)
{
	m_radius = .1f;
	m_height = .5f;
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), in_scale);
	m_type = O_CAPSULE;
	m_collider = new CapsuleCollider(&m_transform, m_height, m_radius);
}

CapsuleObject::CapsuleObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale, float in_radius, float in_height)
{
	m_radius = in_radius;
	m_height = in_height;
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), in_scale);
	m_type = O_CAPSULE;
	m_collider = new CapsuleCollider(&m_transform, m_height, m_radius);
}


void CapsuleObject::draw()
{
	rlPushMatrix();
		applyTransform(m_transform);
		if(m_triangle_mod)
		{
		drawCapsule(m_height, m_radius, 10, m_color, RL_TRIANGLES);
		}
		if (m_wireframe_mod)
		{
			drawCapsule(m_height, m_radius, 10, BLACK, RL_LINES);
		}

	rlPopMatrix();
}

BoxObject::BoxObject()
{
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), Vector3f(1.f, 1.f, 1.f));
	m_type = O_BOX;
	m_collider = new BoxCollider(&m_transform);
}

BoxObject::BoxObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale)
{
	m_transform = Transform3(in_position, in_rotation, in_scale);
	m_type = O_BOX;
	m_collider = new BoxCollider(&m_transform);
}


void BoxObject::draw()
{
	rlPushMatrix();
		applyTransform(m_transform);
		if (m_triangle_mod)
		{
			drawBox(m_transform.m_scale, m_color, RL_TRIANGLES);
		}
		if (m_wireframe_mod)
		{
			drawBox(m_transform.m_scale, BLACK, RL_LINES);
		}
	rlPopMatrix();
}


RoundedBoxObject::RoundedBoxObject()
{
	m_transform = Transform3(vector3Zero(), quaternionIdentity(), Vector3f(1.f, 1.f, 1.f));
	m_radius = .1f;
	m_type = O_ROUNDED_BOX;
	m_collider = new RoundedBoxCollider(&m_transform, m_radius);
}

RoundedBoxObject::RoundedBoxObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale)
{
	m_transform = Transform3(in_position, in_rotation, in_scale);
	m_radius = .1f;
	m_type = O_ROUNDED_BOX;
	m_collider = new RoundedBoxCollider(&m_transform, m_radius);
}


void RoundedBoxObject::draw()
{
	rlPushMatrix();
		applyTransform(m_transform);
		if (m_triangle_mod)
		{
			drawRoundedBox(m_transform.m_scale, m_radius, 10, m_color, RL_TRIANGLES);
		}
		if (m_wireframe_mod)
		{
			drawRoundedBox(m_transform.m_scale, m_radius,10, BLACK, RL_LINES);
		}
	rlPopMatrix();
}