#ifndef GAME_LTNC_CHARACTER_H
#define GAME_LTNC_CHARACTER_H

#include "utils.h"
#include "gameObject.h"

class character : gameObject {
public:
    character();
    ~character();

    enum MoveType {
        RIGHT = 0,
        LEFT = 1,
        UP = 2,
        DOWN = 3,
        IDLE = 4
    };

    bool LoadImg(const string& path, SDL_Renderer* screen) override;
    void Render(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer(Map& map_data);
    void UpdateMap(const int x, const int y) { map_x = x; map_y = y; }

private:
    float x_val, y_val;
    float x_pos, y_pos;
    int width_frame, height_frame;
    int map_x, map_y;
    SDL_Rect frame_clip[FRAME_NUMBER];
    Input input_type;
    unsigned int frame;
    int status;
    int come_back_time;
    bool on_ground;

    void CheckToMap(Map &map_data);
    void CenterEntityOnMap(Map &map_data);
};


#endif //GAME_LTNC_CHARACTER_H
