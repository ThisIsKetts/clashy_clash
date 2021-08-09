#include "raylib.h"
#include "raymath.h"

int main()
{

    // window dimesnions
    const int windowWidth{384};
    const int windowHeight{384};  

    // initialise window
    InitWindow(windowWidth, windowHeight,"Top Down Game");

    // load main map
    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 wmPos{0.0, 0.0};
    float speed{4.0};

    // load character sprites
    Texture2D knight_Idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_Run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos
    {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };


    // 1 : facing right, -1 facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};
    

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {


        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {
            // set wmPos = wmPos - direction
            wmPos = Vector2Subtract(wmPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_Run;
        }
        else
        {
            knight = knight_Idle;
        }

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        // draw the world map
        DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

        // draw the character
        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        // stop drawing
        EndDrawing();

    } 
    UnloadTexture(worldMap);
    CloseWindow();


}