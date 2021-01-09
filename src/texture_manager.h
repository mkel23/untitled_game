#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include "texture.h"

class TextureManager {
  public:
    static TextureManager* Instance();
    TextureManager(TextureManager&) = delete;
    void operator=(const TextureManager&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

    void loadTexture(std::string name, std::string fileName);

    void unloadTexture(std::string name);

    void render(std::string name, int x, int y, SDL_Rect* clip = NULL);

  private:
    static TextureManager* sInstance;

    TextureManager() {};
    ~TextureManager() {};

    void operator delete(void *) {};

    std::map<std::string, Texture> mTexturesByName;
};

#endif
