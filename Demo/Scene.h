#pragma once
#include "Camera.h"
#include "../Include/Intersection3.h"


#include "SceneObject.h"
#include <vector>


enum SceneList
{
	SCENE_SPHERE_COLLISION,
	SCENE_SHAPES_INTERSECTION,
};

class Scene
{
public:
	//	Constructor / Destructor
	//	------------------------
	Scene();
	~Scene();

	//	Functions
	//	---------
	void fixedUpdate(float deltaTime);
	void update(float deltaTime);
	void draw();
	void unload();

private:
	//	Variables
	//	---------
	Cam	m_cam;
	std::vector<SceneObject*> m_shapes;
	Vector3f eulerRotation;
	unsigned int selectedShape = 0;
};
