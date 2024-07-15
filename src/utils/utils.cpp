#include "utils.h"

string getPath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find("cmake-build-debug");
    string tmp = string(buffer).substr(0, pos);
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] == '\\') {
            tmp[i] = '/';
        }
    }
    return tmp;
}
