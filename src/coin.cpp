//
// Created by ADMIN on 8/12/2024.
//

#include "header/item.h"

item::item() {
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    come_back_time = 0;
    on_ground = false;
    frame = 0;

    animation_a = 0;
    animation_b = 0;
    input_type.left = 1;
}

item::~item() {
//    Free();
}

bool item::LoadImg(string path, SDL_Renderer* screen) {   // giống character ?
    bool ret = gameObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect.w / COIN_FRAME_NUMBER;
        height_frame = rect.h;
    }
    return ret;
}

void item::set_clips() {    // giống character ?
    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < COIN_FRAME_NUMBER; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void item::Render(SDL_Renderer *screen) {  // khac character 1 xiu?
    if (come_back_time == 0) {
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;
        frame++;
        if (frame >= COIN_FRAME_NUMBER) frame = 0;


        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(screen, object, currentClip, &renderQuad);
    }
}

//void item::DoCoin(Map &map_data) {
//    if (come_back_time == 0) {
//        x_val = 0;
//        y_val += GRAVITY_SPEED;
//        if (y_val >= MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;   // item dung im 1 cho
//
//        if (input_type.left == 1) {
//            x_val -= PLAYER_SPEED;     // Note: add new constant coin_SPEED?
//        } else if (input_type.right == 1) {
//            x_val += PLAYER_SPEED;     // Note: add new constant coin_SPEED?
//        }
//
//        CheckToMap(map_data);
//    } else if (come_back_time > 0) {
//        come_back_time--;
//        if (come_back_time == 0) {
//            InitCoin();
//        }
//    }
//}

//void item::CheckToMap(Map &map_data) {
//
//    int x1 = 0;
//    int x2 = 0;
//    int y1 = 0;
//    int y2 = 0;
//
//    // Check horizontal
//    int height_min = min(height_frame, TILE_SIZE);
//    x1 = (x_pos + x_val) / TILE_SIZE;
//    x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;
//
//    y1 = y_pos / TILE_SIZE;
//    y2 = (y_pos + height_min - 1) / TILE_SIZE;
//
//    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
//        if (x_val > 0) {
//            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
//                x_pos = x2 * TILE_SIZE;
//                x_pos -= width_frame + 1;
//                x_val = 0;
//            }
//        } else if (x_val < 0) {
//            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
//                x_pos = (x1 + 1) * TILE_SIZE;
//                x_val = 0;
//            }
//        }
//    }
//
//    // Check vertical
//    int width_min = min(width_frame, TILE_SIZE);
//    x1 = x_pos / TILE_SIZE;
//    x2 = (x_pos + width_min) / TILE_SIZE;
//
//    y1 = (y_pos + y_val) / TILE_SIZE;
//    y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;
//
//    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
//        if (y_val > 0) {
//            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
//                y_pos = y2 * TILE_SIZE;
//                y_pos -= (height_frame + 1);
//                y_val = 0;
//                on_ground = true;
//            }
//        } else if (y_val < 0) {
//            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
//                y_pos = (y1 + 1) * TILE_SIZE;
//                y_val = 0;
//            }
//        }
//    }
//
//    x_pos += x_val;
//    y_pos += y_val;
//
//    if (x_pos < 0) {
//        x_pos = 0;
//    } else if (x_pos + width_frame > MAX_MAP_X * TILE_SIZE) {
//        x_pos = MAX_MAP_X * TILE_SIZE - width_frame;
//    }
//
//}
//
//
//
//void item::InitCoin() {
//    x_val = 0;
//    y_val = 0;
//
//    if (x_pos > 4 * TILE_SIZE) {
//        x_pos -= 4 * TILE_SIZE;
//        animation_a -= 4 * TILE_SIZE;
//        animation_b -= 4 * TILE_SIZE;
//    } else {
//        x_pos = 0;
//    }
//    y_pos = 0;
//    come_back_time = 0;
//    input_type.left = 1;
//}


