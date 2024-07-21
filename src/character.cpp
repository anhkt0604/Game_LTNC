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
    on_ground = false;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.up = 0;
    input_type.down = 0;
    map_x = 0;
    map_y = 0;
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

    rect.x = x_pos - map_x;
    rect.y = y_pos - map_y;

    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    SDL_RenderCopy(screen, object, current_clip, &renderQuad);
}

bool character::LoadImg(const string &path, SDL_Renderer *screen) {
    bool result = gameObject::LoadImg(path, screen);
    if (result) {
        width_frame = rect.w / FRAME_NUMBER;
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
                input_type.left = 0;
                break;
            case SDLK_LEFT:
                status = LEFT;
                input_type.left = 1;
                input_type.right = 0;
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

    // NUMBER OF FRAME PER SECOND: 12
    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < FRAME_NUMBER; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void character::DoPlayer(Map &map_data) {
    x_val = 0;
    y_val += GRAVITY_SPEED;
    if (y_val >= MAX_FALL_SPEED) {
        y_val = MAX_FALL_SPEED;
    }

    if (input_type.left == 1) {
        x_val -= PLAYER_SPEED;
    } else if (input_type.right == 1) {
        x_val += PLAYER_SPEED;
    }

    CheckToMap(map_data);
    CenterEntityOnMap(map_data);
}

void character::CheckToMap(Map &map_data) {
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    // Check horizontal
    int height_min = min(height_frame, TILE_SIZE);
    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

    y1 = y_pos / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_val > 0) {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                x_pos = x2 * TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        } else if (x_val < 0) {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
        }
    }

    // Check vertical
    int width_min = min(width_frame, TILE_SIZE);
    x1 = x_pos / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val > 0) {
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                y_pos = y2 * TILE_SIZE;
                y_pos -= (height_frame + 1);
                y_val = 0;
                on_ground = true;
            }
        } else if (y_val < 0) {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                y_pos = (y1 + 1) * TILE_SIZE;
                y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0) {
        x_pos = 0;
    } else if (x_pos + width_frame > MAX_MAP_X * TILE_SIZE) {
        x_pos = MAX_MAP_X * TILE_SIZE - width_frame;
    }
}

void character::CenterEntityOnMap(Map &map_data) {
    map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
    if (map_data.start_x < 0) {
        map_data.start_x = 0;
    } else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x) {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if (map_data.start_y < 0) {
        map_data.start_y = 0;
    } else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y) {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

