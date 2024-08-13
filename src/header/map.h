#ifndef GAME_LTNC_MAP_H
#define GAME_LTNC_MAP_H

#include "utils.h"
#include "gameObject.h"
#include "item.h"
#include <cstdio>

#define MAX_TILES 20
#define COIN_TILE 4
#define TRAP_TILE 5


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
//    vector <item*> MakeCoinsList();
    vector<vector<int>> GetCoinList() const { return coin_list; }
    vector<threatTile> GetThreatList() const { return threat_list; }

    Map getMap() { return gMap; }
    void setMap(Map &map) { gMap = map; }
//    void render();
//    void free();
//    int getWidth();
//    int getHeight();
//    tile* getTile(int x, int y);

private:
    Map gMap;
    tile tiles[MAX_TILES];

    vector<vector<int>> coin_list;
    vector<threatTile> threat_list;
    void GetObject(int &id, const int i, const int j);
};


#endif //GAME_LTNC_MAP_H
