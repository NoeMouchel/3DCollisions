#pragma once


#include "../Include/RigidBody3.h"
#include "../Include/Collider3.h"
#include "../Include/Transform3.h"

#include "Draw.h"

enum ObjectType
{
	O_SPHERE,
	O_CAPSULE,
	O_BOX,
	O_ROUNDED_BOX,
};

class SceneObject
{
public:
	//	Constructor / Destructor
	//	------------------------
	SceneObject() = default;
	~SceneObject();

	//	Components
	//	----------
	ToolBox::Transform3  m_transform;
	ToolBox::RigidBody3* m_rigid_body = nullptr;
	ToolBox::Collider3 * m_collider = nullptr;

	//	Variables
	//	---------
	ToolBox::Vector3f newPos;
	Color	m_color = WHITE;
	bool	m_wireframe_mod = true;
	bool	m_triangle_mod = true;
	int		m_type;
	//	Functions
	//	---------
	void addRigidBody();
	void removeRigidBody();
	void removeCollider();
	void update(float deltaTime);


	//	Virtual Functions
	//	-----------------
	virtual void draw() = 0;
};



class SphereObject : public SceneObject
{
public:
	//	Constructor
	//	-----------
	SphereObject();
	SphereObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale);
	SphereObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale, float in_radius);

	//	Variables
	//	---------
	float m_radius;

	//	Functions Override
	//	------------------
	void draw() override;
};




class CapsuleObject : public SceneObject
{
public:
	//	Constructor
	//	-----------
	CapsuleObject();
	CapsuleObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale);
	CapsuleObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale, float in_radius, float in_height);

	//	Variables
	//	---------
	float m_height;
	float m_radius;

	//	Functions Override
	//	------------------
	void draw() override;
};




class BoxObject : public SceneObject
{
public:
	//	Constructor
	//	-----------
	BoxObject();
	BoxObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale);

	//	Functions Override
	//	------------------
	void draw() override;
};


class RoundedBoxObject : public SceneObject
{
public:
	//	Constructor
	//	-----------
	RoundedBoxObject();
	RoundedBoxObject(const ToolBox::Vector3f& in_position, const ToolBox::Quaternion& in_rotation, const ToolBox::Vector3f& in_scale);

	//	Variables
	//	---------
	float m_radius;

	//	Functions Override
	//	------------------
	void draw() override;
};

