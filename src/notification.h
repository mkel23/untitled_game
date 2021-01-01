#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

class Notification {
  public:
    Notification(std::string text, TTF_Font* font);

    void update();

    void render();

  private:
    // TODO: maybe move these into a struct, and then each notification "type" can have a different const to define relevant details
    const int FRAME_DURATION = 120;
    const int WIDTH = 200, HEIGHT = 50;
    const int BORDER_SIZE = 4;

    SDL_Rect mBox;

    int mTextX, mTextY;

    Texture mTextTexture;

    int mRemainingFrames = FRAME_DURATION;
};

#endif
