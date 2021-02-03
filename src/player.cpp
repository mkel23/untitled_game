#include "constants.h"
#include "collision_manager.h"
#include "game.h"
#include "input_handler.h"
#include "texture_manager.h"
#include "player.h"

Player::Player(std::vector<std::shared_ptr<Tile>>* tiles, int x, int y, int direction) {
  loadMedia();

  mTargetX = x;
  mTargetY = y;

  mBox.x = mTargetX;
  mBox.y = mTargetY;

  mBox.w = PLAYER_WIDTH;
  mBox.h = PLAYER_HEIGHT;

  mDirection = direction;

  mMoving = false;

  mTiles = tiles;
}

Player::~Player() {
  TextureManager::Instance()->unloadTexture("player");
}

void Player::loadMedia() {
  TextureManager::Instance()->loadTexture("player", "res/img/player.png");

  for (int direction = 0; direction < static_cast<int>(PlayerDirection::TOTAL); ++direction) {
    mPlayerClips.push_back(std::vector<SDL_Rect>());
    for (int spriteFrame = 0; spriteFrame < PLAYER_SPRITE_FRAMES; ++spriteFrame) {
      SDL_Rect clip;
      clip.x = spriteFrame * 32;
      clip.y = direction * 32;
      clip.w = PLAYER_WIDTH;
      clip.h = PLAYER_HEIGHT;
      mPlayerClips.back().push_back(clip);
    }
  }
}

void Player::update() {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
    if (mTargetY == mBox.y) {
      mTargetY -= PLAYER_HEIGHT;
      mDirection = static_cast<int>(PlayerDirection::UP);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
    if (mTargetY == mBox.y) {
      mTargetY += PLAYER_HEIGHT;
      mDirection = static_cast<int>(PlayerDirection::DOWN);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
    if (mTargetX == mBox.x) {
      mTargetX -= PLAYER_WIDTH;
      mDirection = static_cast<int>(PlayerDirection::LEFT);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
    if (mTargetX == mBox.x) {
      mTargetX += PLAYER_WIDTH;
      mDirection = static_cast<int>(PlayerDirection::RIGHT);
      mMoving = true;
    }
  }
}

void Player::move(Level* level) {
  int velX = 0, velY = 0;

  if (mTargetX > mBox.x) {
    velX = PLAYER_VEL;
  }

  if (mTargetX < mBox.x) {
    velX = -PLAYER_VEL;
  }

  mBox.x += velX;

  if ((mBox.x < 0) || (mBox.x + PLAYER_WIDTH > level->width()) || touchesWall(mBox, mTiles)) {
    mBox.x -= velX;
    mTargetX = mBox.x;
  }

  if (mTargetY > mBox.y) {
    velY = PLAYER_VEL;
  }

  if (mTargetY < mBox.y) {
    velY = -PLAYER_VEL;
  }

  mBox.y += velY;

  if ((mBox.y < 0) || (mBox.y + PLAYER_HEIGHT > level->height()) || touchesWall(mBox, mTiles)) {
    mBox.y -= velY;
    mTargetY = mBox.y;
  }

  if (mTargetX == mBox.x && mTargetY == mBox.y) {
    mMoving = false;
  }
}

void Player::setCamera(Level* level) {
  // TODO: this feels a little dirty. Should have a function on Game that allows to set X/Y coords on camera. And maybe this should exist in PlayState instead
  SDL_Rect* camera = Game::Instance()->camera();

  camera->x = (mBox.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
  camera->y = (mBox.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

  // TODO: we can wrap these adjustments inside of a check in order to make the camera follow always for smaller levels? or maybe all levels (and then we can just make the borders of the levels have a few sets of trees or whatever in order to not show the background)?

  if (camera->x < 0) {
    camera->x = 0;
  }

  if (camera->x > level->width() - camera->w) {
    camera->x = level->width() - camera->w;
  }

  if (camera->y < 0) {
    camera->y = 0;
  }

  if (camera->y > level->height() - camera->h) {
    camera->y = level->height() - camera->h;
  }
}

void Player::render(int frame) {
  int playerFrame = mMoving ? frame : 0;
  SDL_Rect* camera = Game::Instance()->camera();

  TextureManager::Instance()->render("player", mBox.x - camera->x, mBox.y - camera->y, &mPlayerClips[mDirection][playerFrame]);
}

SDL_Rect* Player::box() {
  return &mBox;
}

int Player::direction() {
  return mDirection;
}
