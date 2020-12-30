#include <fstream>
#include "constants.h"
#include "game.h"
#include "play_state.h"

PlayState::PlayState() {
  loadMedia();
  setTiles();
  mPlayer = new Player(mTiles);
}

PlayState::~PlayState() {
  mTileSheetTexture.free();

  for (int i = 0; i < TOTAL_TILES; ++i) {
    if (mTiles[i] != NULL) {
      delete mTiles[i];
      mTiles[i] = NULL;
    }
  }
}

void PlayState::update() {
  mPlayer->update();
  mPlayer->move();
  mPlayer->setCamera();
}

void PlayState::render(int frame) {
  for (int i = 0; i < TOTAL_TILES; ++i) {
    mTiles[i]->render(Game::Instance()->renderer(), *Game::Instance()->camera());
  }

  mPlayer->render(frame);

  renderDebugGrid();
}

void PlayState::renderDebugGrid() {
  SDL_Renderer* renderer = Game::Instance()->renderer();
  SDL_Rect* camera = Game::Instance()->camera();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

  for (int i = 0; i < LEVEL_HEIGHT / Tile::TILE_HEIGHT; i++) {
    SDL_RenderDrawLine(renderer, 0 - camera->x, i*32 - camera->y, LEVEL_WIDTH - camera->x, i*32 - camera->y);
  }

  for (int i = 0; i < LEVEL_WIDTH / Tile::TILE_WIDTH; i++) {
    SDL_RenderDrawLine(renderer, i*32 - camera->x, 0 - camera->y, i*32 - camera->x, LEVEL_HEIGHT - camera->y);
  }
}

void PlayState::loadMedia() {
  mTileSheetTexture.loadFromFile(Game::Instance()->renderer(), "res/img/tile.png");

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

// TODO: should probably live on Level instead to allow different areas. also error handling here
void PlayState::setTiles() {
  int x = 0, y = 0;

  std::ifstream map("res/maps/main.map");

  for (int i = 0; i < TOTAL_TILES; ++i) {
    int tileType = -1;

    map >> tileType;

    if (map.fail()) break;

    if ((tileType >= 0) && (tileType < Tile::TOTAL_TILE_SPRITES)) {
      mTiles[i] = new Tile(&mTileSheetTexture, mTileClips, x, y, tileType);
    } else {
      break;
    }

    x += Tile::TILE_WIDTH;

    if (x >= LEVEL_WIDTH) {
      x = 0;
      y += Tile::TILE_HEIGHT;
    }
  }
}
