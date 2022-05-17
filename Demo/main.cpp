
#include "Camera.h"
#include "Scene.h"
#include "../Include/Intersection3.h"


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1600;
    int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(30);

    Scene scene;
    SetTargetFPS(60);

    float deltaStock = 0.f;
    float fixedTime = 0.02f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        //  Avoid disturbance from moving the window
        if (deltaTime > .3f)
            deltaTime = .3f;

        deltaStock += deltaTime;
        if (deltaStock >= fixedTime)
        {
            scene.fixedUpdate(deltaTime);
            deltaStock = 0.f;
        }

        scene.update(deltaTime);
        scene.draw();
    }

    scene.unload();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}