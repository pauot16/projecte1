#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "items.h"
#include <vector>

#define G 900
#define PLAYER_JUMP_SPD 450.0f
#define PLAYER_HOR_SPD 400.0f

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta)
{
    float playerWidth = 20.0f;
    float playerHeight = 40.0f;

    Rectangle playerRect = { player->position.x - playerWidth / 2, player->position.y - playerHeight / 2, playerWidth, playerHeight };

    // Store the intended horizontal movement
    float horizontalMovement = 0.0f;
    if (IsKeyDown(KEY_A)) horizontalMovement -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_D)) horizontalMovement += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_W) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    bool hitObstacle = false;
    bool hitCeiling = false;
    bool hitLeft = false;
    bool hitRight = false;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;

        if (ei->blocking && CheckCollisionRecs(playerRect, ei->rect))
        {
            // Calculate the overlap on each side
            float overlapLeft = playerRect.x + playerRect.width - ei->rect.x;
            float overlapRight = ei->rect.x + ei->rect.width - playerRect.x;
            float overlapTop = playerRect.y + playerRect.height - ei->rect.y;
            float overlapBottom = ei->rect.y + ei->rect.height - playerRect.y;

            // Find the minimum overlap to determine the side of collision
            float minOverlap = fminf(fminf(overlapLeft, overlapRight), fminf(overlapTop, overlapBottom));

            if (minOverlap == overlapTop && player->speed > 0)
            {
                // Collision from the top (standing on the platform)
                hitObstacle = true;
                player->speed = 0.0f;
                player->position.y = ei->rect.y - playerHeight / 2;
            }
            else if (minOverlap == overlapBottom && player->speed < 0)
            {
                // Collision from the bottom (hitting the ceiling)
                hitCeiling = true;
                player->speed = 0.0f;
                player->position.y = ei->rect.y + ei->rect.height + playerHeight / 2;
            }
            else if (minOverlap == overlapLeft)
            {
                // Collision from the left side
                hitLeft = true;
                player->position.x = ei->rect.x - playerWidth / 2;
            }
            else if (minOverlap == overlapRight)
            {
                // Collision from the right side
                hitRight = true;
                player->position.x = ei->rect.x + ei->rect.width + playerWidth / 2;
            }
        }
    }

    // Apply horizontal movement only if not blocked by a collision
    if (!(hitLeft && horizontalMovement < 0) && !(hitRight && horizontalMovement > 0))
    {
        player->position.x += horizontalMovement;
    }

    // If no collision, update player position and apply gravity
    if (!hitObstacle && !hitCeiling)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;  // Apply gravity
        player->canJump = false; // Can't jump unless on the ground
    }
    else if (hitCeiling)
    {
        player->canJump = false; // Can jump only if the player is on the ground
    }
    else
    {
        player->canJump = true; // Can jump only if the player is on the ground
    }
}