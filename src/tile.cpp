#include "constants.h"
#include "collision_manager.h"
#include "tile.h"

Tile::Tile(int x, int y, int tileType) {
  mBox.x = x;
  mBox.y = y;

  mBox.w = TILE_WIDTH;
  mBox.h = TILE_HEIGHT;

  mType = tileType;

  // TODO: clean this up
  int plain = static_cast<int>(TileTypes::PLAIN);
  mTileClips[plain].x = 0;
  mTileClips[plain].y = 0;
  mTileClips[plain].w = 32;
  mTileClips[plain].h = 32;

  int grass = static_cast<int>(TileTypes::GRASS);
  mTileClips[grass].x = 32;
  mTileClips[grass].y = 0;
  mTileClips[grass].w = 32;
  mTileClips[grass].h = 32;

  int rock = static_cast<int>(TileTypes::ROCK);
  mTileClips[rock].x = 64;
  mTileClips[rock].y = 0;
  mTileClips[rock].w = 32;
  mTileClips[rock].h = 32;

  int tallGrass = static_cast<int>(TileTypes::TALL_GRASS);
  mTileClips[tallGrass].x = 0;
  mTileClips[tallGrass].y = 32;
  mTileClips[tallGrass].w = 32;
  mTileClips[tallGrass].h = 32;
}

void Tile::render(SDL_Rect& camera) {
  if (checkCollision(camera, mBox)) {
    TextureManager::Instance()->render("tile", mBox.x - camera.x, mBox.y - camera.y, &mTileClips[mType]);
  }
}

int Tile::getType() {
  return mType;
}

SDL_Rect Tile::getBox() {
  return mBox;
}
