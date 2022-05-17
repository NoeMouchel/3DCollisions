#include <iostream>
#include <rlgl.h>

#include "../Include/Utils.h"

#include "DemoFunction.h"
#include "Scene.h"


#define TIME_SPEED  1.f
#define ROTATION_SPEED  1.f

//  Constructors of the Scene
//  ------------------------

Scene::Scene()
{
   
    m_shapes.push_back(new SphereObject({ 0.f,2.f,0.f }, quaternionIdentity(), .1f));
    m_shapes.back()->addRigidBody();
    m_shapes.back()->m_wireframe_mod = false;
    /**/

    //  Obstacle

    for (int i = -2; i < 3; i++)
    {
        //  Random angles
        float a = (float)(rand() % 180);
        float b = (float)(rand() % 180);
        float c = (float)(rand() % 180);
        float d = (float)(rand() % 180);

        m_shapes.push_back(new BoxObject({ 0.f,.5f, (float)i*1.5f }, quaternionFromEuler(a, d, b), { .25f,.25f,.25f }));
        m_shapes.back()->m_color = BLUE;

        m_shapes.push_back(new SphereObject({ 1.5f,.5f, (float)i * 1.5f }, quaternionFromEuler(b, b, c), { .25f,.25f,.25f }, .25f));
        m_shapes.back()->m_color = BLUE;

        m_shapes.push_back(new BoxObject({ 3.f,.5f, (float)i * 1.5f }, quaternionFromEuler(c, b, b), { .25f,.25f,.25f }));
        m_shapes.back()->m_color = BLUE;

        m_shapes.push_back(new RoundedBoxObject({ -1.5f,.5f, (float)i * 1.5f }, quaternionFromEuler(b, a, b), { .25f,.25f,.25f }));
        m_shapes.back()->m_color = BLUE;

        m_shapes.push_back(new BoxObject({ -3.f,.5f, (float)i * 1.5f }, quaternionFromEuler(d, b, a), { .25f,.25f,.25f }));
        m_shapes.back()->m_color = BLUE;
    }


    //  Structure
    m_shapes.push_back(new BoxObject({ 0.f,-.05f, 0.f }, quaternionIdentity(), { 4.f,.1f,4.f }));
    m_shapes.back()->m_color = ORANGE;
    m_shapes.back()->m_triangle_mod = false;

    m_shapes.push_back(new BoxObject({ 4.f,2.f, 0.f }, quaternionIdentity(), { .1f,2.f,4.f }));
    m_shapes.back()->m_color = DARKBROWN;
    m_shapes.back()->m_triangle_mod = false;

    m_shapes.push_back(new BoxObject({ -4.f,2.f, 0.f }, quaternionIdentity(), { .1f,2.f,4.f }));
    m_shapes.back()->m_color = DARKBROWN;
    m_shapes.back()->m_triangle_mod = false;

    m_shapes.push_back(new BoxObject({ 0.f,2.f, 4.f }, quaternionIdentity(), { 4.f,2.f,.1f }));
    m_shapes.back()->m_color = DARKBROWN;
    m_shapes.back()->m_triangle_mod = false;

    m_shapes.push_back(new BoxObject({ 0.f,2.f,-4.f }, quaternionIdentity(), { 4.f,2.f,.1f }));
    m_shapes.back()->m_color = DARKBROWN;
    m_shapes.back()->m_triangle_mod = false;
}


//  Destructor of the scene
//  -----------------------
Scene::~Scene()
{
    unload();
}


void Scene::unload()
{
    //  Delete all shapes instances
   //  ---------------------------

    while (m_shapes.empty() == false)
    {
        delete m_shapes.back();
        m_shapes.pop_back();
    }
}


//  FixedUpdate is called at a same frequence
//  -----------------------------------------
void Scene::fixedUpdate(float deltaTime)
{

    for (SceneObject* currentShape : m_shapes)
    {
        if (currentShape->m_rigid_body != nullptr)
        {
            currentShape->m_rigid_body->preCalculateNextPos(deltaTime);


            if (currentShape->m_type == O_SPHERE)
            {
                SphereObject* currentBall = (SphereObject*)currentShape;
                for (SceneObject* otherShape : m_shapes)
                {
                    if (currentShape == otherShape)         continue;
                    if (otherShape->m_collider == nullptr)  continue;
                    otherShape->m_collider->checkCollisionSphere(*currentBall->m_rigid_body, currentBall->m_radius, deltaTime);

                }
            }
        }
        currentShape->update(deltaTime);
    }
}


//  Update is called in each frame
//  ------------------------------
void Scene::update(float deltaTime)
{  
    eulerRotation.x += (-(int)IsKeyDown(KEY_KP_4) + (int)IsKeyDown(KEY_KP_6)) * ROTATION_SPEED * DEG_TO_RAD;
    eulerRotation.y += (-(int)IsKeyDown(KEY_KP_7) + (int)IsKeyDown(KEY_KP_9)) * ROTATION_SPEED * DEG_TO_RAD;
    eulerRotation.z += (-(int)IsKeyDown(KEY_KP_5) + (int)IsKeyDown(KEY_KP_8)) * ROTATION_SPEED * DEG_TO_RAD;
    m_shapes[selectedShape]->m_transform.m_rotation = quaternionFromEuler(eulerRotation);

    int old_selected = selectedShape;
    selectedShape = loop((int)selectedShape + IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT), 0, (int)m_shapes.size()-1);

    if (selectedShape != old_selected)
    {
        eulerRotation = m_shapes[selectedShape]->m_transform.m_rotation.toEuler();
    }
}



void Scene::draw()
{
    m_cam.Update();

    //  Begin draw + Clear background + Begin 3D mode
    //  ----------------------------------
    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode3D(m_cam.m_camera3D);


    //  Draw Grid + Guizmo
    //  ------------------
    DrawGrid(10, 0.25f);
    drawMyGuizmo();

    //  Display scene shapes
    //  --------------------
    for (SceneObject* currentShape : m_shapes)
    {
        currentShape->draw(); continue;
    }

    //  End 3D Mode
    //  -----------
    EndMode3D();

    //  Draw Fps on Top Left
    DrawFPS(0, 0);

    //  End Drawing
    //  -----------
    EndDrawing();
}

