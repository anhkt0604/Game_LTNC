#ifndef GAME_LTNC_MAIN_H
#define GAME_LTNC_MAIN_H

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gameObject.h"
using namespace std;

string getPath();

const string PROJECT_SOURCE_DIR = getPath();
const string ICON = PROJECT_SOURCE_DIR + "res/icon.png";
const string BACKGROUND = PROJECT_SOURCE_DIR + "res/background.png";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static SDL_Surface* gIcon = NULL;

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 255;

gameObject gBackground;

bool init();
bool loadBackground();
void close();

#endif //GAME_LTNC_MAIN_H
