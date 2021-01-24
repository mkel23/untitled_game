#include <algorithm>
#include "constants.h"
#include "game.h"
#include "input_handler.h"
#include "menu.h"

constexpr SDL_Rect Menu::FULL_WIDTH_BACKGROUND;
constexpr SDL_Rect Menu::SIDE_WIDTH_BACKGROUND;

Menu::Menu (std::vector<std::pair<std::string, void(*)()>> labelsAndCallbacks, bool fullWidth) {
  mMenuFont = TTF_OpenFont("res/fonts/gameboy.ttf", FONT_SIZE);

  mFullWidth = fullWidth;

  if (mFullWidth) {
    mBackground = FULL_WIDTH_BACKGROUND;
  } else {
    mBackground = SIDE_WIDTH_BACKGROUND;
  }

  for (int i = 0; i < labelsAndCallbacks.size(); ++i) {
    mItems.push_back(new MenuItem(i, labelsAndCallbacks[i].first, mMenuFont, labelsAndCallbacks[i].second, mFullWidth));
  }
}

Menu::~Menu() {
  TTF_CloseFont(mMenuFont);
  mMenuFont = NULL;
}

void Menu::update() {
  // TODO: need a way to debounce this
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
    mSelectedItemIndex = std::max(0, mSelectedItemIndex - 1);
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
    mSelectedItemIndex = std::min(static_cast<int>(mItems.size() - 1), mSelectedItemIndex + 1);
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
    mItems[mSelectedItemIndex]->callCallback();
  }
}

void Menu::render() {
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &mBackground);

  for (int i = 0; i < mItems.size(); ++i) {
    bool selected = mSelectedItemIndex == i;
    mItems[i]->render(selected);
  }
}
