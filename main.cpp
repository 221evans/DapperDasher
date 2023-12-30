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
    bool collision{};
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

    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x};

    Texture2D background = LoadTexture("../textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("../textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("../textures/foreground.png");
    float fgX{};
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);
        // scroll background
        bgX -= 20 * deltaTime;
        if(bgX <= -background.width*2)
        {
            bgX = 0.0;
        }
        // scroll midground
        mgX -= 40 * deltaTime;
        if(mgX <= -midground.width*2)
        {
            mgX = 0.0;
        }
        // scroll foreground
        fgX -= 80 * deltaTime;
        if (fgX <= -foreground.width * 2)
        {
            fgX = 0.0;
        }

        // draw background
        Vector2  bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos,0.0, 2.0,WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0,};
        DrawTextureEx(background, bg2Pos,0.0, 2.0, WHITE);

        // draw midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2  mg2Pos{mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // draw foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2  fg2Pos{fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

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
        // update finish line
        finishLine += nebulaVel * deltaTime;

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


        for(AnimData nebula: nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                        nebula.pos.x + pad,
                        nebula.pos.y + pad,
                        nebula.rec.width - 2*pad,
                        nebula.rec.height - 2*pad
                    };
            Rectangle  scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        // draw player
        if (collision)
        {
            DrawText("You Lose!" ,windowDimensions[0] / 4, windowDimensions[1] / 2, 40,WHITE);

        }
        else if(scarfyData.pos.x > finishLine)
        {
            DrawText("You Win!" ,windowDimensions[0] / 4, windowDimensions[1] / 2, 40,WHITE);
        }
        else
        {
            DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // draw nebula
                DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
            }


        }






        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}
