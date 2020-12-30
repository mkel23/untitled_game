#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

class MenuButton {
  public:
    MenuButton(int x, int y, int width, int height, std::string text, TTF_Font* font, int borderSize = 0, void (*callback)() = 0);

    void render();

    bool isClicked();

    void callCallback();

  private:
    SDL_Rect mBox;

    int mTextX, mTextY;

    Texture mTextTexture;

    int mBorderSize;

    void (*mCallback)();
};

#endif
