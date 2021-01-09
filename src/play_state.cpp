#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include "constants.h"
#include "game.h"
#include "input_handler.h"
#include "pause_menu_state.h"
#include "save_state_manager.h"
#include "play_state.h"

PlayState::PlayState(int x, int y, int direction) {
  loadMedia();
  loadTiles();
  mPlayer = new Player(&mTiles, x, y, direction);
  SaveStateManager::Instance()->setPlayer(mPlayer);
}

PlayState::~PlayState() {
  TextureManager::Instance()->unloadTexture("tile");
}

void PlayState::update() {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->gameStateManager()->pushState(new PauseMenuState);
  }

  mPlayer->update();
  mPlayer->move();
  mPlayer->setCamera();
}

void PlayState::render(int frame) {
  for (int i = 0; i < mTiles.size(); ++i) {
    mTiles[i]->render(*Game::Instance()->camera());
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
  TextureManager::Instance()->loadTexture("tile", "res/img/tile.png");
}

// TODO: tile/map loading should be done in a different Level class
/** TODO:
 * Keeping this here (along with saveTiles) for now in order to be able to quickly add new maps (via simple files) and
 * then save to JSON for easy editing. Eventually, I would like to ship using binary outputs, but may introduce some
 * DEV config option that allows me to tinker with the JSON ones before exporting as binary. This will probably come
 * when I make the LevelEditor */
void PlayState::loadSimpleMap() {
  int x = 0, y = 0;

  std::ifstream map("res/maps/main.map");

  for (int i = 0; i < TOTAL_TILES; ++i) {
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

    if (x >= LEVEL_WIDTH) {
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
}
