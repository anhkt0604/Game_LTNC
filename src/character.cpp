#include "header/character.h"

character::character() {
    frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = START_GAME_X_POS;
    y_pos = START_GAME_Y_POS;
    width_frame = 0;
    height_frame = 0;
    status = IDLE;
    on_ground = false;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    map_x = 0;
    map_y = 0;
    come_back_time = 0;

    score = 0;
}

character::~character() {

}


void character::Render(SDL_Renderer *screen) {

    UpdatePlayerImage(screen);

//    if (input_type.left == 1 || input_type.right == 1) {
//        frame++;
//    } else {
//        frame = 0;
//    }

    frame++;

    if (frame >= PLAYER_FRAME_NUMBER) {
        frame = 0;
    }

    if (come_back_time == 0) {
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;

        SDL_Rect* current_clip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(screen, object, current_clip, &renderQuad);
    }
}

bool character::LoadImg(const string &path, SDL_Renderer *screen) {
    bool result = gameObject::LoadImg(path, screen);
    if (result) {
        width_frame = rect.w / PLAYER_FRAME_NUMBER;
        height_frame = rect.h;
//        frame_clip[0].x = 0;
//        frame_clip[0].y = 0;
//        frame_clip[0].w = width_frame;
//        frame_clip[0].h = height_frame;
    }
    return result;
}

void character::HandleInputAction(SDL_Event events, SDL_Renderer *screen) {
//    if (events.type == SDL_USEREVENT) {
//        status = DEAD;
//        input_type.left = 0;
//        input_type.right = 0;
//        input_type.jump = 0;
//        UpdatePlayerImage(screen);
//    }
    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {
            case SDLK_RIGHT:
                status = RIGHT;
                input_type.right = 1;
                input_type.left = 0;
                UpdatePlayerImage(screen);
                break;
            case SDLK_LEFT:
                status = LEFT;
                input_type.left = 1;
                input_type.right = 0;
                UpdatePlayerImage(screen);
                break;
            case SDLK_UP:
                input_type.jump = 1;
                break;
            default:
                status = IDLE;
                input_type.left = 0;
                input_type.right = 0;
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
            case SDLK_UP:
                input_type.jump = 0;
                break;
            default:
                status = IDLE;
                input_type.left = 0;
                input_type.right = 0;
                break;
        }
    }
}

void character::set_clips() {

    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < PLAYER_FRAME_NUMBER; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void character::DoPlayer(Map &map_data) {
    if (come_back_time == 0) {
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

        if (input_type.jump == 1) {
            if (on_ground) {
                y_val = - JUMP_SPEED;
            }
            on_ground = false;
            input_type.jump = 0;
        }

        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }

    if (come_back_time > 0) {
        come_back_time--;
        if (come_back_time == 0) {
            on_ground = false;
            // after die, come back the position before die
            if (x_pos > 0) {
                x_pos -= 6* TILE_SIZE;     // 6 tiles
                // NEW IDEA: check if x_pos is a hole or not, if yes, move to the left until x_pos is not a hole
//                while (map_data.tile[MAX_MAP_Y][ (int) x_pos / TILE_SIZE] != BLANK_TILE) {
//                    x_pos -= TILE_SIZE;
//                }
            } else {
                x_pos = 0;
            }
            y_pos = START_GAME_Y_POS;
            x_val = 0;
            y_val = 0;
//            map_x = 0;
//            map_y = 0;
        }
    }
}


void character::CheckToMap(Map &map_data) {
    // Define tile positions and dimensions
    int x1, x2, y1, y2;
    int tile_size = TILE_SIZE;
    int map_width = MAX_MAP_X * tile_size;
    int map_height = MAX_MAP_Y * tile_size;

    // Check horizontal collisions
    int height_min = std::min(height_frame, tile_size);
    x1 = (x_pos + x_val) / tile_size;
    x2 = (x_pos + x_val + width_frame - 1) / tile_size;
    y1 = y_pos / tile_size;
    y2 = (y_pos + height_min - 1) / tile_size;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_val > 0) { // Moving right
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                x_pos = x2 * tile_size - width_frame - 1;
                x_val = 0;
            }
        } else if (x_val < 0) { // Moving left
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
                x_pos = (x1 + 1) * tile_size;
                x_val = 0;
            }
        }
    }

    // Check vertical collisions
    int width_min = std::min(width_frame, tile_size);
    x1 = x_pos / tile_size;
    x2 = (x_pos + width_min) / tile_size;
    y1 = (y_pos + y_val) / tile_size;
    y2 = (y_pos + y_val + height_frame - 1) / tile_size;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val > 0) { // Falling down
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                y_pos = y2 * tile_size - height_frame - 1;
                y_val = 0;
                on_ground = true;
            }
        } else if (y_val < 0) { // Jumping up
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                y_pos = (y1 + 1) * tile_size;
                y_val = 0;
            }
        }
    }

    // Update position
    x_pos += x_val;
    y_pos += y_val;

    // Ensure the character stays within the map boundaries
    if (x_pos < 0) {
        x_pos = 0;
    } else if (x_pos + width_frame > map_width) {
        x_pos = map_width - width_frame;
    }

    if (y_pos < 0) {
        y_pos = 0;
    } else if (y_pos + height_frame > map_height) {
        y_pos = map_height - height_frame;
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

    if (y_pos > map_data.max_y) {
        come_back_time = 30;
    } else {
        come_back_time = 0;
    }
}

void character::UpdatePlayerImage(SDL_Renderer *screen) {
    if (on_ground) {
        if (input_type.left == 1) {
            status = LEFT;
        } else if (input_type.right == 1) {
            status = RIGHT;
        } else {
            status = IDLE;
        }

        if (status == RIGHT) {
            LoadImg(PLAYER_RIGHT, screen);
        } else if (status == LEFT) {
            LoadImg(PLAYER_LEFT, screen);
        } else if (status == DEAD) {
            LoadImg(PLAYER_DEAD, screen);
        } else {
            LoadImg(PLAYER_IDLE, screen);
        }
    } else {  // Jump
//        if (status == RIGHT) {
//            LoadImg(PLAYER_JUMP_RIGHT, screen);
//        } else if (status == LEFT) {
//            LoadImg(PLAYER_JUMP_LEFT, screen);
//        }
    }
}

SDL_Rect character::GetRectFrame() {
    SDL_Rect result;
    result.x = rect.x;
    result.y = rect.y;
    result.w = width_frame;
    result.h = height_frame;
    return result;
}

void character::UpdateItems(itemType type) {
    switch (type) {
        case COIN:
            score += 1;
            cout << "Score: " << score << endl;
            break;
        case HEART:

            break;
        default:

            break;
    }
}

void character::SetStatus(const int &state) {
    status = state;
    if (status == DEAD) {
        come_back_time = 30;
    }
}




