#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <tuple>
#include <SDL2/SDL.h>

class InputHandler {
  public:
    static InputHandler* Instance();
    InputHandler(InputHandler&) = delete;
    void operator=(const InputHandler&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;

    void update();

    bool isKeyDown(SDL_Scancode key);

    void reset();

    bool isMouseClicked();

    std::pair<int, int> mouseCoords();

  private:
    const Uint8* mKeyStates;

    // TODO: would be nice to deal with struct here instead of `.first`, `.second`...
    std::pair<int, int> mMouseCoords;

    bool mMouseClicked = false;

    InputHandler();
    ~InputHandler();

    void operator delete(void *) {};

    static InputHandler* sInstance;

    void updateKeyStates();

    void updateMousePos(SDL_Event e);

    void updateMouseClickState(SDL_Event e);
};

#endif
