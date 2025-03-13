#ifndef ITEMS_H
#define ITEMS_H

#include "raylib.h"

class EnvItem {
public:
    Rectangle rect;
    int blocking;
    Color color;

    EnvItem(Rectangle r, int b, Color c) : rect(r), blocking(b), color(c) {}
};

#endif
