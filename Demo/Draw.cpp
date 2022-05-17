#include <raylib.h>
#include <rlgl.h>

#include <vector>

#include "DemoFunction.h"
#include "Draw.h"
#include "../Include/Utils.h"

#define VERTEXLIMIT 10

void drawMyGuizmo()
{
	DrawGizmo({ 0,0,0 });
}

void rlDrawTriangle(Vector3 A, Vector3 B, Vector3 C, int mode, Color in_color)
{
	rlBegin(mode);
	rlColor4ub(in_color.r, in_color.g, in_color.b, in_color.a);

	rlVertex3f(A.x, A.y, A.z);
	rlVertex3f(B.x, B.y, B.z);
	rlVertex3f(C.x, C.y, C.z);

	if (mode == RL_LINES)
		rlVertex3f(A.x, A.y, A.z);
	
	rlEnd();
}

void rlDrawTriangleFromVector3f(ToolBox::Vector3f A, ToolBox::Vector3f B, ToolBox::Vector3f C, int mode, Color in_color)
{
	rlDrawTriangle(Vector3f_to_Vector3(A), Vector3f_to_Vector3(B), Vector3f_to_Vector3(C), mode, in_color);
}



void drawQuad(ToolBox::Vector3f pos, ToolBox::Vector3f normal, ToolBox::Vector3f scale, Color in_color, int mode)
{
	int vertexCount = 6;
	if (mode == RL_LINES) vertexCount = 8;
	if (rlCheckBufferLimit(vertexCount))
		rlglDraw();

	rlPushMatrix();

	rlTranslatef(pos.x, pos.y, pos.z);

	Vector3f vect;
	float angle;

	ToolBox::quaternionFromVector3ToVector3({ 0,1,0 }, normal).toAxisAngle(vect, angle);

	rlRotatef(angle * (float)RAD2DEG, vect.x, vect.y, vect.z);
	rlScalef(scale.x, 1.f, scale.z);

	rlDrawTriangle({ -1.f, 0.f,-1.f }, {-1.f, 0.f, 1.f }, { 1.f, 0.f, 1.f }, mode, in_color);
	rlDrawTriangle({  1.f, 0.f, 1.f }, { 1.f, 0.f,-1.f }, {-1.f, 0.f,-1.f }, mode, in_color);

	rlPopMatrix();
}

Vector3 getSphericalCoordinate(float theta, float phi)
{
	return {
		cosf(phi) * sinf(theta),
		cosf(theta),
		sinf(phi) * sinf(theta)
	};
}

void drawSphere(float radius, int lon, int lat, Color in_color, int mode)
{
	int vertexCount = lon*lat*6;
	if (mode == RL_LINES) vertexCount = lon * lat * 8;
	if (rlCheckBufferLimit(vertexCount))
		rlglDraw();

	rlPushMatrix();

	rlScalef(radius, radius, radius);
	float sectorStep = 2.f * (float)PI / lon;
	float stackStep = (float)PI / lat;

	for (int i = 0; i < lat; i++)
	{
		float phi_0 = sectorStep * i;
		float phi_1 = sectorStep * (i + 1);

		for (int j = 0; j < lon; j++)
		{
			float theta_0 = stackStep * j;
			float theta_1 = stackStep * (j + 1);

			Vector3 ptA = getSphericalCoordinate(theta_0, phi_0);
			Vector3 ptB = getSphericalCoordinate(theta_1, phi_0);
			Vector3 ptC = getSphericalCoordinate(theta_1, phi_1);
			Vector3 ptD = getSphericalCoordinate(theta_0, phi_1);

			rlDrawTriangle(ptA, ptC, ptB, mode, in_color);
			rlDrawTriangle(ptA, ptD, ptC, mode, in_color);
		}
	}

	rlPopMatrix();
}

void drawSpherePortion(float radius, int lon, int lat, int start_phi, int end_phi, int start_theta, int end_theta, Color in_color, int mode)
{
	int vertexCount = (end_phi- start_phi) * (end_theta- start_theta) * 6;
	if (mode == RL_LINES) vertexCount = lon * lat * 8;
	if (rlCheckBufferLimit(vertexCount))
		rlglDraw();

	rlPushMatrix();

	rlScalef(radius, radius, radius);

	float sectorStep = 2.f * (float)PI / lon;
	float stackStep = (float)PI / lat;

	for (int i = start_phi; i < end_phi; i++)
	{
		float phi_0 = sectorStep * i;
		float phi_1 = sectorStep * (i + 1);

		for (int j = start_theta; j < end_theta; j++)
		{
			float theta_0 = stackStep * j;
			float theta_1 = stackStep * (j + 1);

			Vector3 ptA = getSphericalCoordinate(theta_0, phi_0);
			Vector3 ptB = getSphericalCoordinate(theta_1, phi_0);
			Vector3 ptC = getSphericalCoordinate(theta_1, phi_1);
			Vector3 ptD = getSphericalCoordinate(theta_0, phi_1);

			rlDrawTriangle(ptA, ptC, ptB, mode, in_color);
			rlDrawTriangle(ptA, ptD, ptC, mode, in_color);
		}
	}

	rlPopMatrix();
}


void drawCylinder(float height, float radius, int division, Color in_color, int mode)
{
	
	std::vector<Vector3f> vertices;

	float angle = 2 * (float)PI / division;

	for (int i = 0; i < division; i++)
	{
		Vector3f new_vertex;

		//	Get points on the Circle
		new_vertex.x = cosf(angle * i) * radius;
		new_vertex.y = -height * .5f;
		new_vertex.z = sinf(angle * i) * radius;
		vertices.push_back(new_vertex);

		new_vertex.y = height * .5f;
		vertices.push_back(new_vertex);
	}

	int vertices_number = (int)vertices.size();

	int vertexCount = vertices_number / 2 * 12;
	if (mode == RL_LINES) vertexCount = vertices_number/2 * 16;
	if (rlCheckBufferLimit(vertexCount))
		rlglDraw();

	rlPushMatrix();

	for (int i = 0; i < vertices_number; i += 2)
	{
		rlDrawTriangleFromVector3f(
			{ 0.f,-height * .5f,0.f },
			vertices[(i + 0) % vertices_number],
			vertices[(i + 2) % vertices_number],
			mode, in_color
		);
		rlDrawTriangleFromVector3f(
			vertices[(i + 3) % vertices_number],
			vertices[(i + 1) % vertices_number],
			{ 0.f, height * .5f, 0.f },
			mode, in_color
		);
		rlDrawTriangleFromVector3f(
			vertices[(i + 0) % vertices_number],
			vertices[(i + 1) % vertices_number],
			vertices[(i + 2) % vertices_number],
			mode, in_color
		);
		rlDrawTriangleFromVector3f(
			vertices[(i + 3) % vertices_number],
			vertices[(i + 2) % vertices_number],
			vertices[(i + 1) % vertices_number],
			mode, in_color
		);
	}


	rlPopMatrix();
}

void drawCylinderPortion(float height, float radius, int division, int min_div, int max_div, Color in_color, int mode)
{
	std::vector<Vector3f> vertices;

	float angle = 2 * (float)PI / division;

	for (int i = min_div; i <= max_div; i++)
	{
		Vector3f new_vertex;

		//	Get points on the Circle
		new_vertex.x = cosf(angle * i) * radius;
		new_vertex.y = -height * .5f;
		new_vertex.z = sinf(angle * i) * radius;
		vertices.push_back(new_vertex);

		new_vertex.y = height * .5f;
		vertices.push_back(new_vertex);
	}


	int vertices_number = (int)vertices.size();

	int vertexCount = vertices_number / 2 * 12;
	if (mode == RL_LINES) vertexCount = vertices_number / 2 * 16;
	if (rlCheckBufferLimit(vertexCount))
		rlglDraw();

	rlPushMatrix();

	for (int i = 0; i < vertices_number; i += 2)
	{
		rlDrawTriangleFromVector3f(
			vertices[(i + 0) % vertices_number],
			vertices[(i + 1) % vertices_number],
			vertices[(i + 2) % vertices_number],
			mode, in_color
		);
		rlDrawTriangleFromVector3f(
			vertices[(i + 3) % vertices_number],
			vertices[(i + 2) % vertices_number],
			vertices[(i + 1) % vertices_number],
			mode, in_color
		);
	}


	rlPopMatrix();
}


void drawCapsule(float height, float radius, int division, Color in_color, int mode)
{
	rlPushMatrix();

	drawCylinderPortion(height, radius, division,0, division, in_color, mode);

	rlTranslatef(0, -height * .5f, 0);
	drawSpherePortion(radius, division, division, 0, division, division / 2, division, in_color, mode);

	rlTranslatef(0, height, 0);
	drawSpherePortion(radius, division, division, 0, division, 0, division / 2, in_color, mode);

	rlPopMatrix();
}


void drawBox(const ToolBox::Vector3f& in_extension, Color in_color, int mode)
{
	rlPushMatrix();
	rlScalef(in_extension.x, in_extension.y, in_extension.z);
	ToolBox::Vector3f position;

	//	On X axis
	drawQuad({ 1.f, 0.f, 0.f },  { 1, 0, 0 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);
	drawQuad({ -1.f, 0.f, 0.f }, {-1, 0, 0 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);

	//	On Y axis
	drawQuad({ 0.f,-1.f, 0.f }, { 0,-1, 0 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);
	drawQuad({ 0.f, 1.f, 0.f }, { 0, 1, 0 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);

	//	On Z axis
	drawQuad({ 0.f, 0.f,-1.f }, { 0, 0,-1 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);
	drawQuad({ 0.f, 0.f, 1.f }, { 0, 0, 1 }, ToolBox::Vector3f(1, 1, 1), in_color, mode);

	rlPopMatrix();
}

void placeCorner(ToolBox::Vector3f pos, ToolBox::Vector3f sign)
{
	rlTranslatef(pos.x * sign.x, pos.y * sign.y, pos.z * sign.z);
}

void drawRoundedBox(const ToolBox::Vector3f& in_extension,float in_radius, int div, Color in_color, int mode)
{
	in_radius = ToolBox::min(in_extension.x, in_radius);
	in_radius = ToolBox::min(in_extension.y, in_radius);
	in_radius = ToolBox::min(in_extension.z, in_radius);

	int lat = div * 2;
	int lon = div;

	rlPushMatrix();

	//	Sphere Corners
	Vector3f position = in_extension - in_radius;
	{
		int half_lat = lat / 2;
		int one_quarter_lat = lat / 4;
		int three_quarter_lat = lat * 3 / 4;

		int half_lon = lon / 2;
		rlPushMatrix();
		placeCorner(position, { 1,1,1 });
		drawSpherePortion(in_radius, div * 2, div, 0, one_quarter_lat, 0, half_lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,1,1 });
		drawSpherePortion(in_radius, div * 2, div, one_quarter_lat, half_lat, 0, half_lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,-1,1 });
		drawSpherePortion(in_radius, div * 2, div, one_quarter_lat, half_lat, half_lon, lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,-1,-1 });
		drawSpherePortion(in_radius, div * 2, div, half_lat, three_quarter_lat, half_lon, lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 1,-1,-1 });
		drawSpherePortion(in_radius, div * 2, div, three_quarter_lat, lat, half_lon, lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 1,1,-1 });
		drawSpherePortion(in_radius, div * 2, div, three_quarter_lat, lat, 0, half_lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,1,-1 });
		drawSpherePortion(in_radius, div * 2, div, half_lat, three_quarter_lat, 0, half_lon, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 1,-1,1 });
		drawSpherePortion(in_radius, div * 2, div, 0, one_quarter_lat, half_lon, lon, in_color, mode);
		rlPopMatrix();
	}

	//	Cylinder Corners
	{
		int div_cyl = lat;
		int one_quarter_Cyl = div_cyl / 4;
		int half_Cyl = div_cyl / 2;
		int three_quarter_Cyl = div_cyl * 3 / 4;

		rlPushMatrix();
		placeCorner(position, { 1,0,1 });
		drawCylinderPortion(in_extension.y * 2.f - in_radius * 2.f, in_radius, div_cyl, 0, one_quarter_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,0,1 });
		drawCylinderPortion(in_extension.y * 2.f - in_radius * 2.f, in_radius, div_cyl, one_quarter_Cyl, half_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1,0,-1 });
		drawCylinderPortion(in_extension.y * 2.f - in_radius * 2.f, in_radius, div_cyl, half_Cyl, three_quarter_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 1,0,-1 });
		drawCylinderPortion(in_extension.y * 2.f - in_radius * 2.f, in_radius, div_cyl, three_quarter_Cyl, div_cyl, in_color, mode);
		rlPopMatrix();

		//------------------------------

		rlPushMatrix();
		placeCorner(position, { 0, 1, 1 });
		rlRotatef(90.f, 0.f, 0.f, 1.f);
		drawCylinderPortion(in_extension.x * 2.f - in_radius * 2.f, in_radius, div_cyl, 0, one_quarter_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 0, -1, 1 });
		rlRotatef(90.f, 0.f, 0.f, 1.f);
		drawCylinderPortion(in_extension.x * 2.f - in_radius * 2.f, in_radius, div_cyl, one_quarter_Cyl, half_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 0, -1, -1 });
		rlRotatef(90.f, 0.f, 0.f, 1.f);
		drawCylinderPortion(in_extension.x * 2.f - in_radius * 2.f, in_radius, div_cyl, half_Cyl, three_quarter_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 0, 1, -1 });
		rlRotatef(90.f, 0.f, 0.f, 1.f);
		drawCylinderPortion(in_extension.x * 2.f - in_radius * 2.f, in_radius, div_cyl, three_quarter_Cyl, div_cyl, in_color, mode);
		rlPopMatrix();

		//------------------------------

		rlPushMatrix();
		placeCorner(position, { 1, 1, 0 });
		rlRotatef(90.f, 1.f, 0.f, 0.f);
		drawCylinderPortion(in_extension.z * 2.f - in_radius * 2.f, in_radius, div_cyl, three_quarter_Cyl, div_cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { 1,-1, 0 });
		rlRotatef(90.f, 1.f, 0.f, 0.f);
		drawCylinderPortion(in_extension.z * 2.f - in_radius * 2.f, in_radius, div_cyl, 0, one_quarter_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1, -1, 0 });
		rlRotatef(90.f, 1.f, 0.f, 0.f);
		drawCylinderPortion(in_extension.z * 2.f - in_radius * 2.f, in_radius, div_cyl, one_quarter_Cyl, half_Cyl, in_color, mode);
		rlPopMatrix();

		rlPushMatrix();
		placeCorner(position, { -1, 1, 0 });
		rlRotatef(90.f, 1.f, 0.f, 0.f);
		drawCylinderPortion(in_extension.z * 2.f - in_radius * 2.f, in_radius, div_cyl, half_Cyl, three_quarter_Cyl, in_color, mode);
		rlPopMatrix();
	}

	//	On X axis
	drawQuad({ in_extension.x, 0.f, 0.f }, { 1, 0, 0 }, Vector3f(in_extension.y, 1, in_extension.z) - in_radius, in_color, mode);
	drawQuad({ -in_extension.x, 0.f, 0.f }, { -1, 0, 0 }, Vector3f(in_extension.y, 1, in_extension.z) - in_radius, in_color, mode);

	//	On Y axis
	drawQuad({ 0.f,-in_extension.y, 0.f }, { 0,-1, 0 }, Vector3f(in_extension.x, 1, in_extension.z) - in_radius, in_color, mode);
	drawQuad({ 0.f, in_extension.y, 0.f }, { 0, 1, 0 }, Vector3f(in_extension.x, 1, in_extension.z) - in_radius, in_color, mode);

	//	On Z axis
	drawQuad({ 0.f, 0.f,-in_extension.z }, { 0, 0,-1 }, Vector3f(in_extension.x, 1, in_extension.y) - in_radius, in_color, mode);
	drawQuad({ 0.f, 0.f, in_extension.z }, { 0, 0, 1 }, Vector3f(in_extension.x, 1, in_extension.y) - in_radius, in_color, mode);
	
	rlPopMatrix();
}