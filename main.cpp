#include "raylib.h"

int main()
{

    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // player jump variables
    const int jumpVelocity{-600};
    bool isJumping{false};
    int velocity{0};

    // initiate window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // add gravity
    const int gravity{1000};
    // set fps
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

    // animation frame
    int frame{};
    const float updateTime{1.0 / 12.0}; // amount of time before we update animation frame
    float runningTime{0};




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
        //update running time
        runningTime += deltaTime;
        if(runningTime >= updateTime)
        {
            runningTime = 0;
            // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame ++;
            if (frame > 5)
            {
                frame = 0;
            }
        }


        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
