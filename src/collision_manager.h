#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL2/SDL.h>
#include "tile.h"

bool checkCollision(SDL_Rect a, SDL_Rect b);

bool checkInBounds(SDL_Rect a, int x, int y);

bool touchesWall(SDL_Rect box, std::vector<Tile*>* tilesPtr);

#endif
