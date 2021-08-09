#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    // window dimesnions
    const int windowWidth{384};
    const int windowHeight{384};

    // initialise window
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    // load main map
    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 wmPos{0.0, 0.0};
   
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        wmPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        // stop drawing
        EndDrawing();
    }
    CloseWindow();
}