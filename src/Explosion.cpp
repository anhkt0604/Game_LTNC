//
// Created by ADMIN on 8/13/2024.
//

#include "header/Explosion.h"

Explosion::Explosion() {
    frame = 0;
    rect.x = 0;
    rect.y = 0;
    width_frame = 0;
    height_frame = 0;
}

Explosion::~Explosion() {

}

void Explosion::Render(SDL_Renderer *screen) {
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    if (current_clip != NULL) {
        renderQuad.w = current_clip->w;
        renderQuad.h = current_clip->h;
    }
    SDL_RenderCopy(screen, object, current_clip, &renderQuad);
}

bool Explosion::LoadImg(const string &path, SDL_Renderer *screen) {
    bool ret = gameObject::LoadImg(path, screen, 0, 0, 0);
    if (ret) {
        width_frame = rect.w / EXPLOSION_FRAME_NUMBER;
        height_frame = rect.h;
    }
    return ret;
}

void Explosion::set_clips() {
    for (int i = 0; i < EXPLOSION_FRAME_NUMBER; i++) {
        frame_clip[i].x = i * width_frame;
        frame_clip[i].y = 0;
        frame_clip[i].w = width_frame;
        frame_clip[i].h = height_frame;
    }
}


