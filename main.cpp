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
    Texture2D nebula = LoadTexture("../textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec;
    nebulaRec.width = nebula.width/8;
    nebulaRec.height = nebula.height/8;
    nebulaRec.x = 0;
    nebulaRec.y = 0;
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};
    // nebula x velocity
    int nebulaVel{-200};

    // nebula 2 variables
    Rectangle nebula2Rec;
    nebula2Rec.width = nebula.width/8;
    nebulaRec.height = nebula.height/8;
    nebula2Rec.x = 0;
    nebulaRec.y = 0;
    Vector2 nebula2Pos{windowWidth + 300, windowHeight - nebulaRec.height};



    // player variables
    Texture2D scarfy = LoadTexture("../textures/scarfy.png");
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

    int nebula2Frame{};
    const float nebula2UpdateTime{1.0/16.0};
    float nebula2RunningTime{0};


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

        // update neb2 position
        nebula2Pos.x += nebulaVel * deltaTime;

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

        if (nebula2RunningTime >= nebula2UpdateTime)
        {
            nebula2RunningTime = 0.0;
            nebula2Rec.x = nebula2Frame * nebula2Rec.width;
            nebula2Frame ++;
            if(nebula2Frame > 7)
            {
                nebula2Frame = 0;
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
        // draw second nebula
        DrawTextureRec(nebula,nebula2Rec, nebula2Pos, RED);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
