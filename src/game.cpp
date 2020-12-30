#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "input_handler.h"
#include "main_menu_state.h"
#include "player.h"
#include "game.h"

Game* Game::sInstance = 0;

Game* Game::Instance() {
  if (sInstance == 0) {
    sInstance = new Game();
  }

  return sInstance;
}

bool Game::setup() {
  bool success = true;

  if (!init()) {
    success = false;
  }

  mGameStateManager.pushState(new MainMenuState);
  mRunning = true;
  mCamera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

  return success;
}

void Game::run() {
  int frame = 0;

  while (mRunning) {
    InputHandler::Instance()->update();

    mGameStateManager.update();

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    mGameStateManager.render(frame / 8);

    // TODO: clean up this frame stuff to account for capped fps
    ++frame;

    if (frame / 8 >= Player::PLAYER_SPRITE_FRAMES) {
      frame = 0;
    }

    SDL_RenderPresent(mRenderer);

    InputHandler::Instance()->reset();
  }
}

void Game::teardown() {
  SDL_DestroyRenderer(mRenderer);
  mRenderer = NULL;

  SDL_DestroyWindow(mWindow);
  mWindow = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool Game::init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
  } else {
    mWindow = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == NULL) {
      success = false;
    } else {
      mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      if (mRenderer == NULL) {
        success = false;
      } else {
        int imgFlags = IMG_INIT_PNG;

        if (!(IMG_Init(imgFlags) & imgFlags)) {
          success = false;
        }

        if (TTF_Init() == -1) {
          success = false;
        }
      }
    }
  }

  return success;
}

void Game::quit() {
  mRunning = false;
}

SDL_Renderer* Game::renderer() {
  return mRenderer;
}

SDL_Rect* Game::camera() {
  return &mCamera;
}

GameStateManager* Game::gameStateManager() {
  return &mGameStateManager;
}
