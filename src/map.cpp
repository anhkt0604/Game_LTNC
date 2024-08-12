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
        vector<int> tmp;
        tmp.push_back(j * TILE_SIZE);
        tmp.push_back(i * TILE_SIZE);
        coin_list.push_back(tmp);
    }
}

//vector<coin*> GameMap::MakeCoinsList() {
//    vector <coin*> list_coins;
//    coin* coin_obj = new coin[20];
//    for (int i = 0; i < 20; i++) {
//        coin* p_coin = (coin_obj + i);
//        if (p_coin == NULL) {
//            cout << "Memory allocation failed!" << endl;
//            return list_coins;
//        } else {
//            p_coin->LoadImg(PROJECT_SOURCE_DIR + "res/map/4.png", gRenderer);
//            p_coin->set_clips();
//            p_coin->setX_pos(700 + i * 1200);
//            p_coin->setY_pos(250);
//            p_coin->setInputLeft(0);
//
//            list_coins.push_back(p_coin);
//        }
//    }
//
//    return list_coins;
//}
