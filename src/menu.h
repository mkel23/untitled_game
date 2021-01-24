#ifndef MENU_H
#define MENU_H

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.h"
#include "menu_item.h"

class Menu {
  public:
    Menu(std::vector<std::pair<std::string, void(*)()>> labelsAndCallbacks, bool fullWidth = false);
    ~Menu();

    void update();
    void render();

    // X Y W H
    static constexpr SDL_Rect FULL_WIDTH_BACKGROUND = {
      (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 4),
      (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT - 20) / 2),
      SCREEN_WIDTH / 2,
      SCREEN_HEIGHT - 20
    };

    // X Y W H
    static constexpr SDL_Rect SIDE_WIDTH_BACKGROUND = {
      SCREEN_WIDTH - (SCREEN_WIDTH / 4),
      (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT - 20) / 2),
      SCREEN_WIDTH / 4,
      SCREEN_HEIGHT - 20
    };

  protected:
    const int FONT_SIZE = 16;

    bool mFullWidth;

    SDL_Rect mBackground;

    std::vector<MenuItem*> mItems;

    int mSelectedItemIndex = 0;

    TTF_Font* mMenuFont;
};

#endif
