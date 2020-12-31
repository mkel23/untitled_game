#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu_button.h"
#include "game_state.h"

// TODO: would be nice to extract this out to a generic menu (and use for both main and pause)
class MainMenuState : public GameState {
  public:
    MainMenuState();
    ~MainMenuState();

    virtual void update();

    virtual void render(int frame);

  private:
    const int GUTTER_WIDTH = 50, GUTTER_HEIGHT = 20;
    const int BUTTON_HEIGHT = 75;

    const int FONT_SIZE = 16;

    static void newGame();
    static void quit();

    SDL_Rect mBackground;

    std::vector<MenuButton*> mButtons;

    TTF_Font* mMenuFont;
};

#endif
