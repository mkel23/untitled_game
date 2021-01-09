#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <cereal/archives/json.hpp>
#include "game.h"
#include "texture.h"
#include "texture_manager.h"

enum class TileTypes {
  PLAIN,
  GRASS,
  ROCK,
  TALL_GRASS
};

class Tile {
  public:
    static const int TILE_WIDTH = 32;
    static const int TILE_HEIGHT = 32;

    static const int TOTAL_TILE_SPRITES = 4;

    Tile(int x, int y, int tileType);

    void render(SDL_Rect& camera);

    int getType();

    SDL_Rect getBox();

    template<class Archive>
    void serialize(Archive& ar) {
      ar(
        cereal::make_nvp("xCoord", mBox.x),
        cereal::make_nvp("yCoord", mBox.y),
        cereal::make_nvp("type", mType)
      );
    }

    template<class Archive>
    static void load_and_construct(Archive& ar, cereal::construct<Tile>& construct) {
      TextureManager::Instance()->loadTexture("tile", "res/img/tile.png");

      int x, y, tileType;
      ar(x, y, tileType);
      construct(x, y, tileType);
    }

  private:
    SDL_Rect mBox;

    int mType;

    SDL_Rect mTileClips[Tile::TOTAL_TILE_SPRITES];
};

#endif
