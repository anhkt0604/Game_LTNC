#include "header/map.h"

void GameMap::LoadMap(char *path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        cout << "Cannot open file " << path << endl;
        return;
    }

    gMap.max_x = 0;
    gMap.max_y = 0;
    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {
            fscanf(file, "%d", &gMap.tile[i][j]);
            int value = gMap.tile[i][j];

            GetObject(gMap.tile[i][j], i, j);

            if (value > 0) {
                if (j > gMap.max_x) {
                    gMap.max_x = j;
                }

                if (i > gMap.max_y) {
                    gMap.max_y = i;
                }
            }
        }
    }

    gMap.max_x = (gMap.max_x + 1) * TILE_SIZE;
    gMap.max_y = (gMap.max_y + 1) * TILE_SIZE;

    gMap.start_x = 0;
    gMap.start_y = 0;
    gMap.file_name = path;
    fclose(file);
}

void GameMap::LoadTiles(SDL_Renderer *renderer) {
    char file_img[30];
    FILE* file = NULL;
    for (int i = 0; i < MAX_TILES; i++) {
        string tmp = PROJECT_SOURCE_DIR + "res/map/" + to_string(i) + ".png";
        strcpy(file_img, tmp.c_str());
        file = fopen(file_img, "r");
        if (file == NULL) {
            cout << "Cannot open file " << file_img << endl;
            continue;
        }
        fclose(file);
        tiles[i].LoadImg(file_img, renderer);
    }
}

void GameMap::DrawMap(SDL_Renderer *renderer) {
    int x1 = gMap.start_x / TILE_SIZE;
    int x2 = (gMap.start_x + gMap.max_x) / TILE_SIZE;
    int y1 = gMap.start_y / TILE_SIZE;
    int y2 = (gMap.start_y + gMap.max_y) / TILE_SIZE;

    if (x1 < 0) {
        x1 = 0;
    }

    if (y1 < 0) {
        y1 = 0;
    }

    if (x2 >= MAX_MAP_X) {
        x2 = MAX_MAP_X - 1;
    }

    if (y2 >= MAX_MAP_Y) {
        y2 = MAX_MAP_Y - 1;
    }

    int x = 0;
    int y = 0;
    for (int i = y1; i <= y2; i++) {
        x = 0;
        for (int j = x1; j <= x2; j++) {
            int value = gMap.tile[i][j];
            if (value > 0) {
                tiles[value].SetRect(x, y);
                tiles[value].Render(renderer);
            }
            x += TILE_SIZE;
        }
        y += TILE_SIZE;
    }
}

void GameMap::GetObject(int &id, const int i, const int j) {
    if (id == 0) {
        return;
    } else if (id == COIN_TILE) {
        id = 0;
        gMap.object[i][j] = COIN_TILE;
        itemTile tmp;
        tmp.x = j * TILE_SIZE;
        tmp.y = i * TILE_SIZE;
        coin_list.push_back(tmp);
    } else if (id == TRAP_TILE) {
        id = 0;
        gMap.object[i][j] = TRAP_TILE;
        threatTile tmp;
        tmp.x = j * TILE_SIZE;
        tmp.y = i * TILE_SIZE;
        tmp.type = TRAP;
        tmp.isMoving = false;
        threat_list.push_back(tmp);
    } else if (id == KEY_TILE) {
        id = 0;
        gMap.object[i][j] = KEY_TILE;
        key.x = j * TILE_SIZE;
        key.y = i * TILE_SIZE;
    } else if (id == DOOR_TILE) {
        id = 0;
        gMap.object[i][j] = DOOR_TILE;
        door.x = j * TILE_SIZE;
        door.y = i * TILE_SIZE;
    }
}

vector<item *> GameMap::GetCoinList(SDL_Renderer* renderer) {
    vector <item*> list_coins;

    for (int i = 0; i < coin_list.size(); i++) {
        item* p_coin = new item("coin");
        p_coin->LoadImg(COIN_DIR, renderer);
        p_coin->SetTilePos(coin_list[i]);
        p_coin->set_clips();
        p_coin->setX_pos(coin_list[i].x);
        p_coin->setY_pos(coin_list[i].y);
        p_coin->setInputLeft(0);

        list_coins.push_back(p_coin);
    }

    return list_coins;
}

vector<threat *> GameMap::GetThreatList(SDL_Renderer* renderer) {
    vector <threat*> list_threats;
    for (int i = 0; i < threat_list.size(); i++) {
        threat* p_threat = new threat();
        p_threat->SetTilePos(threat_list[i]);
        p_threat->LoadImg(TRAP_DIR, renderer);
        p_threat->set_clips();
        p_threat->setX_pos(threat_list[i].x);
        p_threat->setY_pos(threat_list[i].y);
        if (threat_list[i].isMoving) {
            p_threat->set_type_move(threat::MoveType::MOVE_THREAT);
        } else {
            p_threat->set_type_move(threat::MoveType::STATIC_THREAT);
            p_threat->setInputLeft(0);
        }

        list_threats.push_back(p_threat);
    }

    return list_threats;
}

item *GameMap::GetDoor(SDL_Renderer *renderer) {
    item* p_door = new item("door");
    p_door->SetTilePos(door);
    p_door->LoadImg(DOOR_DIR, renderer);
    p_door->set_clips();
    p_door->setX_pos(door.x);
    p_door->setY_pos(door.y);
    p_door->setInputLeft(0);

    return p_door;
}

item *GameMap::GetKey(SDL_Renderer *renderer) {
    item* p_key = new item("key");
    p_key->SetTilePos(key);
    p_key->LoadImg(KEY_DIR, renderer);
    p_key->set_clips();
    p_key->setX_pos(key.x);
    p_key->setY_pos(key.y);

    return p_key;
}


