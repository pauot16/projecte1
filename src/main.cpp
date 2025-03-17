
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "items.h"
#include <vector>


void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
void UpdateCameraCenterInsideMap(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 850;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Fox Flare");

    Player player = {0};
    player.position = Vector2{ 400, 280 };
    player.speed = 0;
    player.canJump = false;


    EnvItem envItems[] = {
        {{ 0, 0, 2000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 2000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 20 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY },
        {{ 900, 200, 100, 10 }, 1, GRAY }
    };


    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.8f;


    int cameraOption = 1;


    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 0.8f;
            player.position = Vector2{ 400, 280 };
        }

        // Call Camera Function
        UpdateCameraCenterInsideMap(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight); 
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(LIGHTGRAY); 

        BeginMode2D(camera);

        for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

        Rectangle playerRect = { player.position.x - 20, player.position.y - 20, 20.0f, 40.0f };
        DrawRectangleRec(playerRect, RED);

        EndMode2D();

        DrawText("Controls:", 20, 20, 10, BLACK);
        DrawText("- A/D to move", 40, 40, 10, DARKGRAY);
        DrawText("- W to jump", 40, 60, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}