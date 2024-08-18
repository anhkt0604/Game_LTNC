#include "header/utils.h"

string getPath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find("cmake-build-debug");
    string path = string(buffer).substr(0, pos);
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
    return path;
}

bool utils::CheckCollision(TilePos object1, TilePos object2) {
    int o2_x = object2.x / TILE_SIZE;
    int o2_y = object2.y / TILE_SIZE;
    if (object1.x == o2_x && object1.y == o2_y) {
        return true;
    }
    return false;
}