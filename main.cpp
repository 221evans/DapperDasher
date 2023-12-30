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

    const int sizeOfNebulae{10};

    // nebula AnimData Arrays
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }


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

        // update position of each nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebulaVel * deltaTime;
        }




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


        for (int i = 0; i < sizeOfNebulae; i++ )
        {
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame ++;
                if(nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }


        // draw player
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // draw nebula
            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
        }



        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
