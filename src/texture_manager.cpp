#include "game.h"
#include "texture_manager.h"

TextureManager* TextureManager::sInstance = 0;

TextureManager* TextureManager::Instance() {
  if (sInstance == 0) {
    sInstance = new TextureManager();
  }

  return sInstance;
}

void TextureManager::loadTexture(std::string name, std::string fileName) {
  auto iterator = mTexturesByName.find(name);

  if (iterator == mTexturesByName.end()) {
    Texture texture;
    texture.loadFromFile(Game::Instance()->renderer(), fileName);
    mTexturesByName[name] = texture;
  }
}

void TextureManager::unloadTexture(std::string name) {
  auto iterator = mTexturesByName.find(name);

  if (iterator != mTexturesByName.end()) {
    iterator->second.free();
    mTexturesByName.erase(name);
  }
}

void TextureManager::render(std::string name, int x, int y, SDL_Rect* clip) {
  auto iterator = mTexturesByName.find(name);

  if (iterator != mTexturesByName.end()) {
    Texture texture = iterator->second;

    texture.render(x, y, Game::Instance()->renderer(), clip);
  }
}
