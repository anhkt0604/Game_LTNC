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
#define KEY_TILE 6
#define DOOR_TILE 8


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

    item* GetDoor(SDL_Renderer* renderer);
    item* GetKey(SDL_Renderer* renderer);
    
    Map getMap() { return gMap; }
    void setMap(Map &map) { gMap = map; }

private:
    Map gMap;
    tile tiles[MAX_TILES];

    vector<itemTile> coin_list;
    vector<threatTile> threat_list;

    TilePos key;
    TilePos door;

    void GetObject(int &id, const int i, const int j);
};


#endif //GAME_LTNC_MAP_H
