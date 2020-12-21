#include "constants.h"
#include "collision_manager.h"
#include "tile.h"

Tile::Tile(Texture* tileTexture, SDL_Rect* tileClips, int x, int y, int tileType) {
  mBox.x = x;
  mBox.y = y;

  mBox.w = TILE_WIDTH;
  mBox.h = TILE_HEIGHT;

  mType = tileType;

  mTileTexture = tileTexture;
  mTileClips = tileClips;
}

void Tile::render(SDL_Rect& camera) {
  if (checkCollision(camera, mBox)) {
    mTileTexture->render(mBox.x - camera.x, mBox.y - camera.y, &mTileClips[mType]);
  }
}

int Tile::getType() {
  return mType;
}

SDL_Rect Tile::getBox() {
  return mBox;
}
