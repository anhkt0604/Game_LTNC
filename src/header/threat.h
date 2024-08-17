#ifndef GAME_LTNC_THREAT_H
#define GAME_LTNC_THREAT_H

#include "utils.h"
#include "gameObject.h"

class threat : public gameObject {
public:
    threat();
    ~threat();

    enum MoveType {
        STATIC_THREAT = 0,
        MOVE_THREAT = 1,
    };

    void setX_val(const float& xVal) {x_val = xVal;}
    void setY_val(const float& yVal) {y_val = yVal;}

//    void setX_pos(const float& xPos) {x_pos = xPos;}
//    void setY_pos(const float& yPos) {y_pos = yPos;}
//    float getX_pos() const {return x_pos;}
//    float getY_pos() const {return y_pos;}

    void SetMap(const int& x, const int& y) {map_x = x; map_y = y;}
    void set_clips();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);

    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    void DoThreat(Map& map_data);
    void CheckToMap(Map& map_data);

    void set_type_move(const int& type) {type_move = type;}
    void setAnimationPos(const int& a, const int& b) {animation_a = a; animation_b = b;}
    void setInputLeft(const int& val) {input_type.left = val;}
//    void ImpMoveType(SDL_Renderer* screen);

    int get_type_move() const {return type_move;}

    void InitThreat();
private:
    int map_x, map_y;
//    float x_pos, y_pos;
    float x_val, y_val;
    bool on_ground;
    int come_back_time;
    SDL_Rect frame_clip[THREAT_FRAME_NUMBER];
    int width_frame, height_frame;
    int frame;
    int type_move;
    int animation_a, animation_b;
    Input input_type;
};


#endif //GAME_LTNC_THREAT_H
