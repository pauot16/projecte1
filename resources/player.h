#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <vector>

class EnvItem; // Forward declaration to avoid circular dependency

class Player {
public:
    Vector2 position;
    float speed;
    bool canJump;

    Player(); // Constructor
    void Update(std::vector<EnvItem>& envItems, float delta);
};

#endif
