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

bool utils::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (bottom_a <= top_b) return false;
    if (top_a >= bottom_b) return false;
    if (right_a <= left_b) return false;
    if (left_a >= right_b) return false;

    return true;
}