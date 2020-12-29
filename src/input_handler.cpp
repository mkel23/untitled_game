#include "game.h"
#include "input_handler.h"

InputHandler* InputHandler::sInstance = 0;

InputHandler* InputHandler::Instance() {
  if (sInstance == 0) {
    sInstance = new InputHandler();
  }

  return sInstance;
}

InputHandler::InputHandler() {
  mKeyStates = NULL;
}

InputHandler::~InputHandler() {
  delete mKeyStates;
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
  if (mKeyStates != NULL) {
    return mKeyStates[key];
  }

  return false;
}

void InputHandler::update() {
  SDL_Event e;

  // TODO: mouse move events, mouse click events (mostly for menu right now - menus can handle keyboard events later?)
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        Game::Instance()->quit();
        break;
      case SDL_KEYDOWN:
        updateKeyStates();
        break;
      case SDL_KEYUP:
        updateKeyStates();
        break;
      default:
        break;
    }
  }
}

void InputHandler::updateKeyStates() {
  mKeyStates = SDL_GetKeyboardState(NULL);
}
