//
// Created by ADMIN on 8/13/2024.
//

#ifndef GAME_LTNC_EXPLOSION_H
#define GAME_LTNC_EXPLOSION_H

#include "utils.h"
#include "gameObject.h"

#define EXPLOSION_FRAME_NUMBER 9


class Explosion : public gameObject {
private:
    SDL_Rect frame_clip[EXPLOSION_FRAME_NUMBER];
    unsigned int frame;

    int width_frame, height_frame;

public:
    Explosion();
    ~Explosion();

    void Render(SDL_Renderer* screen);
    bool LoadImg(const string& path, SDL_Renderer* screen);

    void set_clips();
    void set_frame(const unsigned int& frame) {this->frame = frame;}
    int get_frame_width() const {return width_frame;}
    int get_frame_height() const {return height_frame;}
};


#endif //GAME_LTNC_EXPLOSION_H
