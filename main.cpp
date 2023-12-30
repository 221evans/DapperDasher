#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;

};

bool IsOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;

}

AnimData UpdateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame ++;
        if(data.frame >= maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

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
        nebulae[i].updateTime = 1.0 / 12.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }

    Texture2D background = LoadTexture("../textures/far-buildings.png");
    float bgX{};
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * deltaTime;

        // draw background
        Vector2  bgPos{bgX, 0.0};
        DrawTextureEx(background, bgPos,0.0, 2.0,WHITE);




        if (IsOnGround(scarfyData, windowDimensions[1]))
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

       if (!isJumping)
       {
           scarfyData = UpdateAnimData(scarfyData,deltaTime,5);
       }


        for (int i = 0; i < sizeOfNebulae; i++ )
        {
            nebulae[i] = UpdateAnimData(nebulae[i], deltaTime, 7);
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
