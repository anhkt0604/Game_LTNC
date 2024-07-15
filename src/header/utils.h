#ifndef GAME_LTNC_UTILS_H
#define GAME_LTNC_UTILS_H

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

string getPath();

const string PROJECT_SOURCE_DIR = getPath();
const string ICON = PROJECT_SOURCE_DIR + "res/icon.png";
const string BACKGROUND = PROJECT_SOURCE_DIR + "res/background.png";
const string MAP = PROJECT_SOURCE_DIR + "res/map/map01.dat";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static SDL_Surface* gIcon = NULL;

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct Map {
    int start_x;
    int start_y;
    int max_x;
    int max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

#endif //GAME_LTNC_UTILS_H
