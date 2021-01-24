#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu_item.h"
#include "game_state.h"
#include "menu.h"

class MainMenuState : public GameState {
  public:
    MainMenuState();

    virtual void update();

    virtual void render(int frame);

  private:
    static void newGame();
    static void quit();

    Menu* mMenu;
};

#endif
