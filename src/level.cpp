#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include "constants.h"
#include "level.h"

Level::Level(std::string levelKey) {
  TextureManager::Instance()->loadTexture("tile", "res/img/tile.png");

  std::string levelPath;

  {
    std::ifstream file("res/map_keys.json");
    cereal::JSONInputArchive archive(file);
    archive(cereal::make_nvp(levelKey, levelPath));
  }

  loadTiles(levelPath);
  loadEntities(levelPath);
}

Level::~Level() {
  TextureManager::Instance()->unloadTexture("tile");
}

std::vector<std::shared_ptr<Tile>>* Level::tiles() {
  return &mTiles;
}

void Level::render() {
  for (int i = 0; i < mTiles.size(); ++i) {
    mTiles[i]->render(*Game::Instance()->camera());
  }

  renderDebugGrid();
}

int Level::tileCount() {
  return mTiles.size();
}

int Level::width() {
  return mWidth;
}

int Level::height() {
  return mHeight;
}

void Level::renderDebugGrid() {
  SDL_Renderer* renderer = Game::Instance()->renderer();
  SDL_Rect* camera = Game::Instance()->camera();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

  for (int i = 0; i < mHeight / Tile::TILE_HEIGHT; i++) {
    SDL_RenderDrawLine(renderer, 0 - camera->x, i*32 - camera->y, mWidth - camera->x, i*32 - camera->y);
  }

  for (int i = 0; i < mWidth / Tile::TILE_WIDTH; i++) {
    SDL_RenderDrawLine(renderer, i*32 - camera->x, 0 - camera->y, i*32 - camera->x, mHeight - camera->y);
  }
}

void Level::loadTiles(std::string filePath) {
  {
    std::ifstream file(filePath);
    cereal::JSONInputArchive archive(file);

    archive(
      cereal::make_nvp("tiles", mTiles),
      cereal::make_nvp("width", mWidth),
      cereal::make_nvp("height", mHeight)
    );
  }
}

void Level::loadEntities(std::string filePath) {
  // TODO: I think instead of trying to put too much logic into the tiles, can just render entities over the tiles
  // This should probably include:
  //   - doors/level portals
  //   - NPCs
  // Also need to decide if we want to setup a different file structure, maybe map and entities live in different files
  // in a shared folder? Idk yet, but whenever I do this...
}

/** TODO:
 * Keeping this here (along with saveTiles) for now in order to be able to quickly add new maps (via simple files) and
 * then save to JSON for easy editing. Eventually, I would like to ship using binary outputs, but may introduce some
 * DEV config option that allows me to tinker with the JSON ones before exporting as binary. This will probably come
 * when I make the LevelEditor */
/* void PlayState::loadSimpleMap() {
  int x = 0, y = 0;

  std::ifstream map("res/maps/main.map");

  for (int i = 0; i < mLevel->tileCount(); ++i) {
    int tileType = -1;

    map >> tileType;

    if (map.fail()) break;

    if ((tileType >= 0) && (tileType < Tile::TOTAL_TILE_SPRITES)) {
      Tile* tile = new Tile(x, y, tileType);
      mTiles.push_back(std::make_shared<Tile>(std::move(*tile)));
    } else {
      break;
    }

    x += Tile::TILE_WIDTH;

    if (x >= mLevel->width()) {
      x = 0;
      y += Tile::TILE_HEIGHT;
    }
  }
}

void PlayState::saveTiles() {
  {
    std::ofstream file("res/maps/main.json");
    cereal::JSONOutputArchive archive(file);

    archive(cereal::make_nvp("tiles", mTiles));
  }
}

void PlayState::loadTiles() {
  {
    std::ifstream file("res/maps/main.json");
    cereal::JSONInputArchive archive(file);

    archive(cereal::make_nvp("tiles", mTiles));
  }
} */
