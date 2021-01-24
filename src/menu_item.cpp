#include "constants.h"
#include "collision_manager.h"
#include "game.h"
#include "input_handler.h"
#include "menu.h"
#include "menu_item.h"

MenuItem::MenuItem(int index, std::string text, TTF_Font* font, void (*callback)(), bool button, int borderSize) {
  if (button) {
    SDL_Rect menuBackground = Menu::FULL_WIDTH_BACKGROUND;

    mBox.x = menuBackground.x + BUTTON_GUTTER_WIDTH;
    // TODO: can we clean this up? idc right now, but eventually
    mBox.y = menuBackground.y + (BUTTON_HEIGHT * index) + BUTTON_GUTTER_HEIGHT + ((index+1) * BUTTON_GUTTER_HEIGHT);
    mBox.w = menuBackground.w - (2 * BUTTON_GUTTER_WIDTH);
    mBox.h = BUTTON_HEIGHT;
  } else {
    SDL_Rect menuBackground = Menu::SIDE_WIDTH_BACKGROUND;

    mBox.x = menuBackground.x + ITEM_GUTTER_WIDTH;
    mBox.y = menuBackground.y + (ITEM_HEIGHT * index) + ITEM_GUTTER_HEIGHT + ((index+1 * ITEM_GUTTER_HEIGHT));
    mBox.w = menuBackground.w - (2 * ITEM_GUTTER_WIDTH);
    mBox.h = ITEM_HEIGHT;
  }

  mTextTexture.loadFromRenderedText(text, font);

  mButton = button;

  if (mButton) {
    // We want the text centered in the button
    mTextX = mBox.x + ((mBox.w / 2) - (mTextTexture.getWidth() / 2));
    mTextY = mBox.y + ((mBox.h / 2) - (mTextTexture.getHeight() / 2));
  } else {
    mTextX = mBox.x + ((mBox.w / 2) - (mTextTexture.getWidth() / 2)) + 25;
    mTextY = mBox.y + ((mBox.h / 2) - (mTextTexture.getHeight() / 2));
  }

  mBorderSize = borderSize;

  mCallback = callback;
}

void MenuItem::render(bool selected) {
  if (mButton) {
    renderButton(selected);
  } else {
    renderItem(selected);
  }
}

void MenuItem::renderButton(bool selected) {
  // Outline first since the button will be drawn on top
  SDL_Rect border = { mBox.x, mBox.y, mBox.w, mBox.h };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &border);

  // Button fill color to create illusion of border
  SDL_Rect fill = { mBox.x + mBorderSize, mBox.y + mBorderSize, mBox.w - (2 * mBorderSize), mBox.h - (2 * mBorderSize) };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &fill);

  // Render text on top
  mTextTexture.render(mTextX, mTextY, Game::Instance()->renderer());

  if (!selected) {
    SDL_Rect overlay = { mBox.x, mBox.y, mBox.w, mBox.h };
    SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0x00, 0x00, 0x00, 0x77);
    SDL_SetRenderDrawBlendMode(Game::Instance()->renderer(), SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(Game::Instance()->renderer(), &overlay);
    SDL_SetRenderDrawBlendMode(Game::Instance()->renderer(), SDL_BLENDMODE_NONE);
  }
}

void MenuItem::renderItem(bool selected) {
  mTextTexture.render(mTextX, mTextY, Game::Instance()->renderer());

  if (selected) {
    SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(Game::Instance()->renderer(), mBox.x, mBox.y + (mBox.h / 2), mBox.x + 25, mBox.y + (mBox.h / 2));
  }
}

void MenuItem::callCallback() {
  (*mCallback)();
}
