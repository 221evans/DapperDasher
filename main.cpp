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


    // nebula variables
    Texture2D nebula = LoadTexture("/Users/jasonevans/Documents/DapperDasher/textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec;
    nebulaRec.width = nebula.width/8;
    nebulaRec.height = nebula.height/8;
    nebulaRec.x = 0;
    nebulaRec.y = 0;
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};
    // nebula x velocity
    int nebulaVel{-200};



    // player variables
    Texture2D scarfy = LoadTexture("/Users/jasonevans/Documents/DapperDasher/textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width /2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // player animation variables
    int frame{};
    const float updateTime{1.0 / 12.0}; // amount of time before we update animation frame
    float runningTime{0};

    // nebula animation variables

    int nebulaFrame{};
    const float  nebulaUpdateTime{1.0 / 12.0};
    float nebulaRunningTime{0};




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

        // update nebula position

        nebulaPos.x += nebulaVel * deltaTime;

        // apply velocity to position
        scarfyPos.y += velocity * deltaTime;

        //update running time
        runningTime += deltaTime;

        // update nebula running time
        nebulaRunningTime += deltaTime;

        if (nebulaRunningTime >= nebulaUpdateTime)
        {
            nebulaRunningTime = 0.0;
            nebulaRec.x = nebulaFrame * nebulaRec.width;
            nebulaFrame ++;
            if(nebulaFrame > 7)
            {
                nebulaFrame = 0;
            }
        }

        if(runningTime >= updateTime && !isJumping)
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

        // draw player
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);
        // draw nebula
        DrawTextureRec(nebula,nebulaRec,nebulaPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
