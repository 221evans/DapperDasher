#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;

};

int main()
{

    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // player jump variables
    const int jumpVelocity{-600};
    bool isJumping{false};
    int velocity{0};

    // initiate window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // add gravity
    const int gravity{1000};
    // set fps
    SetTargetFPS(60);



    // nebula x velocity
    int nebulaVel{-200};

    // nebula variables
    Texture2D nebula = LoadTexture("../textures/12_nebula_spritesheet.png");

    // nebula AnimData
   AnimData nebData;
   nebData.rec.width = nebula.width/8;
   nebData.rec.height = nebula.height/8;
   nebData.pos.x = windowDimensions[0];
   nebData.pos.y = windowDimensions[1] - nebData.rec.height;
   nebData.frame = 0;
   nebData.updateTime = 1.0 / 12.0;
   nebData.runningTime = 0.0;


    // neb2AnimData
    AnimData neb2Data;
    neb2Data.rec.width = nebula.width/8;
    neb2Data.rec.height = nebula.height/8;
    neb2Data.pos.x = windowDimensions[0] + 300;
    neb2Data.pos.y = windowDimensions[1] - nebData.rec.height;
    neb2Data.frame = 0;
    neb2Data.updateTime = 1.0 / 12.0;
    neb2Data.runningTime = 0.0;

    // player variables
    Texture2D scarfy = LoadTexture("../textures/scarfy.png");
    AnimData scarfyData{};
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/ 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        const float deltaTime = GetFrameTime();
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

        nebData.pos.x += nebulaVel * deltaTime;

        // update neb2 position
        neb2Data.pos.x += nebulaVel * deltaTime;

        // apply velocity to position
        scarfyData.pos.y += velocity * deltaTime;

        //update running time
        scarfyData.runningTime += deltaTime;

        // update nebula running time
        nebData.runningTime += deltaTime;

        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame ++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
             neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame ++;
            if(neb2Data.frame> 7)
            {
                neb2Data.frame = 0;
            }
        }

        if(scarfyData.runningTime >= scarfyData.updateTime && !isJumping)
        {
            scarfyData.runningTime = 0;
            // update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame ++;
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
        }

        // draw player
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);
        // draw nebula
        DrawTextureRec(nebula,nebData.rec,nebData.pos,WHITE);
        // draw second nebula
        DrawTextureRec(nebula,neb2Data.rec, neb2Data.pos, RED);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
