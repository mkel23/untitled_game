#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

class MenuItem {
  public:
    MenuItem(int index, std::string text, TTF_Font* font, void (*callback)() = 0, bool button = false, int borderSize = 4);

    void render(bool selected);

    void callCallback();

  private:
    const int BUTTON_GUTTER_WIDTH = 50, BUTTON_GUTTER_HEIGHT = 20;
    const int BUTTON_HEIGHT = 75;

    const int ITEM_GUTTER_WIDTH = 20, ITEM_GUTTER_HEIGHT = 20;
    const int ITEM_HEIGHT = 20;

    SDL_Rect mBox;

    int mTextX, mTextY;

    bool mButton;

    Texture mTextTexture;

    int mBorderSize;

    void (*mCallback)();

    void renderButton(bool selected);

    void renderItem(bool selected);
};

#endif
