#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        wmPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        DrawTextureEx(worldMap, wmPos, 0.0, worldMapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > worldMap.width * worldMapScale ||
            knight.getWorldPos().y + windowHeight > worldMap.height * worldMapScale)
        {
            knight.undoMovement();
        }
        // check prop collisions
        for (auto prop : props)
        {
           if  (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
           {
               knight.undoMovement();
           }
        }

        goblin.tick(GetFrameTime());

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionRecs(goblin.getCollisionRec(), knight.getCollisionRec()))
            {
                goblin.setAlive(false);

            }
        }

        // stop drawing
        EndDrawing();
    }
    CloseWindow();
}