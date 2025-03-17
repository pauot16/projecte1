#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "items.h"
#include <vector>

#define G 1000
#define PLAYER_JUMP_SPD 450.0f
#define PLAYER_HOR_SPD 400.0f

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta)
{
    float playerWidth = 40.0f;   
    float playerHeight = 40.0f; 

    Rectangle playerRect = { player->position.x - playerWidth / 2, player->position.y - playerHeight / 2, playerWidth, playerHeight }; 
    
    if (IsKeyDown(KEY_A)) player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_D)) player->position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    bool hitObstacle = false;
    bool hitCeiling = false;


    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;

        // Check if the player is falling down and collides with the platform (blocking)
        if (ei->blocking && player->speed > 0 &&
            CheckCollisionRecs(playerRect, ei->rect)) // Collision with platform
        {
            hitObstacle = true;
            player->speed = 0.0f;
            player->position.y = ei->rect.y - playerHeight / 2;  // Position player just above the platform
            break;
        }

        // Check if the player is jumping up and collides with the platform (blocking)
        if (ei->blocking && player->speed < 0 &&
            CheckCollisionRecs(playerRect, ei->rect)) // Collision with platform
        {
            hitCeiling = true;
            player->speed = 0.0f;
            player->position.y = ei->rect.y + ei->rect.height + playerHeight / 2;  // Position player just below the ceiling
            break;
        }
    }

    // If no collision, update player position and apply gravity
    if (!hitObstacle && !hitCeiling)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;  // Apply gravity
        player->canJump = false; // Can't jump unless on the ground
    }
    else
    {
        player->canJump = true; // Can jump only if the player is on the ground
    }
}