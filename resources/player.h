#include "raylib.h"
#include <vector>

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;