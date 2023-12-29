#include "raylib.h"

int main()
{

    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    const int jumpVelocity{-600};
    bool isJumping{false};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    const int gravity{1000};
    SetTargetFPS(60);

    Texture2D scarfy = LoadTexture("/Users/jasonevans/Documents/DapperDasher/textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width /2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // rectangle position
    int velocity{0};


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        const float deltaTime = GetFrameTime();
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // ground check
            velocity = 0;
            isJumping = false;
        }
        else
        {
            // apply gravity

            velocity += gravity * deltaTime;
            isJumping = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isJumping)
        {

            velocity += jumpVelocity;

        }

        // apply velocity to position
        scarfyPos.y += velocity * deltaTime;

        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
