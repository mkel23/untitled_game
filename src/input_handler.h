#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
  public:
    static InputHandler* Instance();
    InputHandler(InputHandler&) = delete;
    void operator=(const InputHandler&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;

    void update();

    bool isKeyDown(SDL_Scancode key);

  private:
    const Uint8* mKeyStates;

    InputHandler();
    ~InputHandler();

    void operator delete(void *) {};

    static InputHandler* sInstance;

    void updateKeyStates();
};

#endif
