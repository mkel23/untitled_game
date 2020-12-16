#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "constants.h"
#include "globals.h"
#include "ltexture.h"
#include "player.h"

using namespace std;

SDL_Renderer* gRenderer = NULL;

LTexture gTextTexture;
SDL_Window* gWindow = NULL;

SDL_Rect gTileClips[4];
LTexture gTileSheetTexture;
SDL_Rect gPlayerClips[1];
LTexture gPlayerTexture;

bool init();
bool loadMedia();
void close();
void loop();

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
  } else {
    gWindow = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
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

SDL_Texture* loadTexture(std::string path) {
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

  SDL_FreeSurface(loadedSurface);

  return newTexture;
}

bool loadMedia() {
  bool success = true;

  if (!gTileSheetTexture.loadFromFile("res/tile.png")) {
    success = false;
  } else {
    gTileClips[0].x = 0;
    gTileClips[0].y = 0;
    gTileClips[0].w = 32;
    gTileClips[0].h = 32;

    gTileClips[1].x = 32;
    gTileClips[1].y = 0;
    gTileClips[1].w = 32;
    gTileClips[1].h = 32;

    gTileClips[2].x = 64;
    gTileClips[2].y = 0;
    gTileClips[2].w = 32;
    gTileClips[2].h = 32;

    gTileClips[3].x = 0;
    gTileClips[3].y = 32;
    gTileClips[3].w = 32;
    gTileClips[3].h = 32;
  }

  if (!gPlayerTexture.loadFromFile("res/player.png")) {
    success = false;
  } else {
    gPlayerClips[0].x = 0;
    gPlayerClips[0].y = 0;
    gPlayerClips[0].w = 32;
    gPlayerClips[0].h = 32;
  }

  return success;
}

void close() {
  gTextTexture.free();
  gTileSheetTexture.free();
  gPlayerTexture.free();

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void loop() {
  SDL_Event e;
  bool quit = false;
  Player player(&gPlayerTexture, gPlayerClips);

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      player.handleEvent(e);
    }

    player.move();

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (int i = 0; i < 15; i++) {
      for (int j = 0; j < 20; j++) {
        if (i % 2 == 0) {
          gTileSheetTexture.render(j*32, i*32, &gTileClips[0]);
        } else {
          gTileSheetTexture.render(j*32, i*32, &gTileClips[3]);
        }
      }
    }

    player.render();

    SDL_RenderPresent(gRenderer);
  }
}

int main(int argc, char* args[]) {
  init();
  loadMedia();
  loop();
  close();

  return 0;
}
