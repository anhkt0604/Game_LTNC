#ifndef GAME_LTNC_CHARACTER_H
#define GAME_LTNC_CHARACTER_H

#include "utils.h"
#include "gameObject.h"

class character : gameObject {
public:
    character();
    ~character();

    enum MoveType {
        IDLE = 0,
        RIGHT = 1,
        LEFT = 2,
        DEAD
    };

    bool LoadImg(const string& path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer(Map& map_data);
    void UpdateMap(const int x, const int y) { map_x = x; map_y = y; }
    void UpdatePlayerImage(SDL_Renderer* screen);
    void UpdateItems(itemType type);
    void SetComeBackTime(const int& cb_time) { come_back_time = cb_time; }
    void SetStatus(const int& state);

//    bool CheckCollision(const Map& map_data);

//    int GetTilePosX() const { return tile_pos.x; }
//    int GetTilePosY() const { return tile_pos.y; }
//    TilePos GetTilePos() const { return tile_pos; }

    SDL_Rect GetRectFrame();
    TilePos GetTilePos();

    int GetHeart() const { return heart; }
    int GetScore() const { return score; }
    void useHeart() { heart--; }
    bool isDead() { return heart < 0; }
    void AddHeart() { heart++; }
    void AddScore() { score++; }

    void SetKey(bool k) { key = k; }
    bool GetKey() { return key; }

private:
    float x_val, y_val;
    float x_pos, y_pos;
    int width_frame, height_frame;
    int map_x, map_y;
    SDL_Rect frame_clip[PLAYER_FRAME_NUMBER];
    Input input_type;
    unsigned int frame;
    int status;
    int come_back_time;
    bool on_ground;

    int score;
    int heart;
    bool key;

    void CheckToMap(Map &map_data);
    void CenterEntityOnMap(Map &map_data);

};


#endif //GAME_LTNC_CHARACTER_H
