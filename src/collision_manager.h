#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL2/SDL.h>
#include "tile.h"

bool checkCollision(SDL_Rect a, SDL_Rect b);

bool touchesWall(SDL_Rect box, Tile* tiles[]);

#endif
