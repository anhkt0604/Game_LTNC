#ifndef GAME_LTNC_UTILS_H
#define GAME_LTNC_UTILS_H

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
using namespace std;

string getPath();

const string PROJECT_SOURCE_DIR = getPath();
const string ICON = PROJECT_SOURCE_DIR + "res/icon.png";
const string BACKGROUND = PROJECT_SOURCE_DIR + "res/background.png";
const string MAP = PROJECT_SOURCE_DIR + "res/map/map01.dat";
const string PLAYER_RIGHT = PROJECT_SOURCE_DIR + "res/player_right.png";
const string PLAYER_LEFT = PROJECT_SOURCE_DIR + "res/player_left.png";
const string PLAYER_IDLE = PROJECT_SOURCE_DIR + "res/player_idle.png";
const string PLAYER_DEAD = PROJECT_SOURCE_DIR + "res/player_dead.png";
const string TRAP_DIR = PROJECT_SOURCE_DIR + "res/trap.png";
const string COIN_DIR = PROJECT_SOURCE_DIR + "res/coin.png";
const string EXPLOSION_DIR = PROJECT_SOURCE_DIR + "res/explosion.png";

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

const int SCREEN_BPP = 32;

const int RENDER_DRAW_COLOR = 0xFF;
const int FRAME_PER_SECOND = 20;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define PLAYER_FRAME_NUMBER 8
#define THREAT_FRAME_NUMBER 8

#define GRAVITY_SPEED 1
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10
#define JUMP_SPEED 20

#define START_GAME_Y_POS 200
//#define START_GAME_X_POS 100

enum itemType {COIN = 4, HEART};
enum threatType {TRAP = 5};

typedef struct Input {
    int left;
    int right;
    int jump;
};

typedef struct Map {
    int start_x;
    int start_y;
    int max_x;
    int max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    int object[MAX_MAP_Y][MAX_MAP_X] = {0};
    char* file_name;
};

struct TilePos {
    int x, y;

    // Toán tử so sánh < để có thể sử dụng Point làm khóa trong std::map
    bool operator<(const TilePos& other) const {
        // So sánh theo trật tự từ điển (lexicographical order)
        if (x < other.x) return true;
        if (x == other.x && y < other.y) return true;
        return false;
    }
};

// Định nghĩa một hàm để in Point ra màn hình
inline ostream& operator<<(ostream& os, const TilePos& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
};

struct threatTile : TilePos {
    threatType type;
    bool isMoving;
};

struct itemTile : TilePos {
    itemType type;
};

namespace utils {
    bool CheckCollision(TilePos object1, TilePos object2);
}


#endif //GAME_LTNC_UTILS_H
