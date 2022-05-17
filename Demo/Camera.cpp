#include "Camera.h"

Cam::Cam()
{
	m_camera3D.fovy = 45.f;
	m_camera3D.position = { 1.f,1.f,1.f };
	m_camera3D.target = { 0.f,0.f,0.f };
	m_camera3D.type = CAMERA_PERSPECTIVE;
	m_camera3D.up = { 0.f,1.f,0.f };

	SetCameraMode(m_camera3D, CAMERA_FREE);
}

void Cam::Update()
{
	UpdateCamera(&m_camera3D);
}