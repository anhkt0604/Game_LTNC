#ifndef GAME_LTNC_MAP_H
#define GAME_LTNC_MAP_H

#include "utils.h"
#include "gameObject.h"
#include "item.h"
#include "threat.h"
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
    vector<item*> GetCoinList(SDL_Renderer* renderer);
    vector<threat*> GetThreatList(SDL_Renderer* renderer);


    Map getMap() { return gMap; }
    void setMap(Map &map) { gMap = map; }
//    void render();
//    void free();
//    int getWidth();
//    int getHeight();
//    tile* getTile(int x, int y);

//    int GetThreatIndex(TilePos pos) { return threat_map[pos]; }
//    int GetCoinIndex(TilePos pos) { return coin_map[pos]; }

private:
    Map gMap;
    tile tiles[MAX_TILES];

    vector<itemTile> coin_list;
    vector<threatTile> threat_list;

//    map<TilePos, int> coin_map;
//    map<TilePos, int> threat_map;

    void GetObject(int &id, const int i, const int j);
};


#endif //GAME_LTNC_MAP_H
