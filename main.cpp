#include "raylib.h"

int main()
{

    // window dimesnions
    const int windowWidth{384};
    const int windowHeight{384};  

    // initialise window
    InitWindow(windowWidth, windowHeight,"Top Down Game");

    // load main map
    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT {GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the world map
        Vector2 wmPos{0.0, 0.0};
        DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

        // stop drawing
        EndDrawing();


    } 

    UnloadTexture(worldMap);
    CloseWindow();


}