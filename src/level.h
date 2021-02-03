#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "tile.h"

class Level {
  public:
    Level(std::string levelKey);
    ~Level();

    std::vector<std::shared_ptr<Tile>>* tiles();

    void render();

    int tileCount();

    int width();
    int height();

  private:
    int mWidth, mHeight;
    std::vector<std::shared_ptr<Tile>> mTiles;

    void loadTiles(std::string filePath);
    void loadEntities(std::string filePath);

    void renderDebugGrid();
};

#endif
