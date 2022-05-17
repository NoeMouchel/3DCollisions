#pragma once
#include <raylib.h>

#include "../Include/Shapes3.h"

//	Draw Function of differents shapes
//	----------------------------------

void drawMyGuizmo();

void drawQuad(ToolBox::Vector3f pos, ToolBox::Vector3f normal, ToolBox::Vector3f scale, Color in_color, int mode);

void drawSphere(float radius, int lon, int lat, Color in_color, int mode);

void drawSpherePortion(float radius, int lon, int lat, int start_phi, int end_phi, int start_theta, int end_theta, Color in_color, int mode);

void drawCylinder(float height, float radius, int division, Color in_color, int mode);

void drawCylinderPortion(float height, float radius, int division, int min_div, int max_div, Color in_color, int mode);

void drawCapsule(float height, float radius, int division, Color in_color, int mode);

void drawBox(const ToolBox::Vector3f& in_extension, Color in_color, int mode);

void drawRoundedBox(const ToolBox::Vector3f& in_extension, float in_radius, int div, Color in_color, int mode);