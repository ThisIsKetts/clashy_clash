#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

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
    const float worldMapScale{4.0f};
   
    Character knight{windowWidth, windowHeight};

    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        wmPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        DrawTextureEx(worldMap, wmPos, 0.0, worldMapScale, WHITE);

        rock.Render(knight.getWorldPos());

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > worldMap.width * worldMapScale||
            knight.getWorldPos().y + windowHeight > worldMap.height * worldMapScale)
        {
            knight.undoMovement();
        }

        // stop drawing
        EndDrawing();
    }
    CloseWindow();
}