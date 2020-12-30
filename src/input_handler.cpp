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

bool InputHandler::isMouseClicked() {
  return mMouseClicked;
}

std::pair<int, int> InputHandler::mouseCoords() {
  return mMouseCoords;
}

void InputHandler::update() {
  SDL_Event e;

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
      case SDL_MOUSEMOTION:
        updateMousePos(e);
      case SDL_MOUSEBUTTONUP:
        if (e.button.button == SDL_BUTTON_LEFT) {
          updateMouseClickState(e);
        }
      default:
        break;
    }
  }
}

void InputHandler::updateKeyStates() {
  mKeyStates = SDL_GetKeyboardState(NULL);
}

void InputHandler::updateMousePos(SDL_Event e) {
  mMouseCoords.first = e.motion.x;
  mMouseCoords.second = e.motion.y;
}

void InputHandler::updateMouseClickState(SDL_Event e) {
  mMouseClicked = true;
}

void InputHandler::reset() {
  mMouseClicked = false;
}
