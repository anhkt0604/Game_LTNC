#ifndef GAME_LTNC_MAP_H
#define GAME_LTNC_MAP_H

#include "utils.h"
#include "gameObject.h"
#include <cstdio>

#define MAX_TILES 20

class tile : public gameObject {
public:
    tile() {;}
    ~tile() {;}
};

class GameMap {
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* path);
    void LoadTiles(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);
//    void render();
//    void free();
//    int getWidth();
//    int getHeight();
//    tile* getTile(int x, int y);

private:
    Map gMap;
    tile tiles[MAX_TILES];
};


#endif //GAME_LTNC_MAP_H
