#include "header/character.h"

character::character() {
    frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
}

character::~character() {

}

void character::Render(SDL_Renderer *screen) {
    if (status == RIGHT) {
        LoadImg(PROJECT_SOURCE_DIR + "res/player_right.png", screen);
    } else if (status == LEFT) {
        LoadImg(PROJECT_SOURCE_DIR + "res/player_left.png", screen);
    }

    if (input_type.left == 1 || input_type.right == 1) {
        frame++;
    } else {
        frame = 0;
    }

    if (frame >= 8) {
        frame = 0;
    }

    rect.x = x_pos;
    rect.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    SDL_RenderCopy(screen, object, current_clip, &renderQuad);
}

bool character::LoadImg(const string &path, SDL_Renderer *screen) {
    bool result = gameObject::LoadImg(path, screen);
    if (result) {
        width_frame = rect.w / 8;
        height_frame = rect.h;
//        frame_clip[0].x = 0;
//        frame_clip[0].y = 0;
//        frame_clip[0].w = width_frame;
//        frame_clip[0].h = height_frame;
    }
    return result;
}

void character::HandleInputAction(SDL_Event events, SDL_Renderer *screen) {
    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {
            case SDLK_RIGHT:
                status = RIGHT;
                input_type.right = 1;
                break;
            case SDLK_LEFT:
                status = LEFT;
                input_type.left = 1;
                break;
            default:
                break;
        }
    } else if (events.type == SDL_KEYUP) {
        switch (events.key.keysym.sym) {
            case SDLK_RIGHT:
                input_type.right = 0;
                break;
            case SDLK_LEFT:
                input_type.left = 0;
                break;
            default:
                break;
        }
    }
}

void character::set_clips() {
    if (width_frame > 0 && height_frame > 0) {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2 * width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 3 * width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 4 * width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 5 * width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;

        frame_clip[6].x = 6 * width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7 * width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;
    }
}
