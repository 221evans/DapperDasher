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

    // nebula AnimData Arrays
    AnimData nebulae[2]{nebData, neb2Data};



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

        nebulae[0].pos.x += nebulaVel * deltaTime;

        // update neb2 position
        nebulae[1].pos.x += nebulaVel * deltaTime;

        // apply velocity to position
        scarfyData.pos.y += velocity * deltaTime;

        //update running time
        scarfyData.runningTime += deltaTime;

        // update nebula running time
        nebulae[0].runningTime += deltaTime;

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


        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame ++;
            if(nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame ++;
            if(nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }


        // draw player
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);
        // draw nebula
        DrawTextureRec(nebula,nebulae[0].rec,nebulae[0].pos,WHITE);
        // draw second nebula
        DrawTextureRec(nebula,nebulae[1].rec, nebulae[1].pos, RED);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
