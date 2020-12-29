#include "constants.h"
#include "game.h"
#include "play_state.h"

PlayState::PlayState() {
  mPlayer = new Player();
}

void PlayState::update() {
  mPlayer->update();
  mPlayer->move();
  mPlayer->setCamera();
}

void PlayState::render(int frame) {
  mPlayer->render(frame);
}
