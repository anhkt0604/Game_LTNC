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