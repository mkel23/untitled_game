#include "tile.h"
#include "game.h"
#include "collision_manager.h"

bool checkCollision(SDL_Rect a, SDL_Rect b) {
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }

  return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[]) {
  for (int i = 0; i < Game::TOTAL_TILES; ++i) {
    if ((tiles[i]->getType() == static_cast<int>(TileTypes::ROCK))) {
      if (checkCollision(box, tiles[i]->getBox())) {
        return true;
      }
    }
  }

  return false;
}
