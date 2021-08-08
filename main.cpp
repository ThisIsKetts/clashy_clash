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

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos
    {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT {GetFrameTime()};

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
        }

        // draw the world map
        DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

        // draw the character
        Rectangle source{0.f, 0.f, (float)knight.width/6.0f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        // stop drawing
        EndDrawing();


    } 

    UnloadTexture(worldMap);
    CloseWindow();


}