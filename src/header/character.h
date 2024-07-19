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
    };

    bool LoadImg(const string& path, SDL_Renderer* screen) override;
    void Render(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

private:
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[8];
    Input input_type;
    unsigned int frame;
    int status;
};


#endif //GAME_LTNC_CHARACTER_H
