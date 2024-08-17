#include "header/utils.h"
#include "header/gameObject.h"
#include "header/map.h"
#include "header/character.h"
#include "header/timer.h"
#include "header/threat.h"
#include "header/explosion.h"

bool initSDL();

gameObject gBackground;
bool loadBackground();

// Implement timer (fps)
timer fps_timer;

void close();
void process();

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return -1;
    }
    if (!loadBackground()) {
        return -1;
    }

    process();

    close();
    return 0;
}

bool initSDL() {

    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    } else {
        cout << "SDL initialized!" << endl;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        cout << "Warning: Linear texture filtering not enabled!" << endl;
    }

    // Create window
    gWindow = SDL_CreateWindow("Game LTNC",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Set Window Icon
    gIcon = IMG_Load(ICON.c_str());
    if (gIcon == NULL) {
        cout << "Icon could not be loaded! SDL_Error: " << SDL_GetError() << endl;
    } else {
        SDL_SetWindowIcon(gWindow, gIcon);
        SDL_FreeSurface(gIcon);
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    } else {
        SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
            return false;
        }
    }

    return success;
}

bool loadBackground() {
    bool success = true;
    if (!gBackground.LoadImg(BACKGROUND, gRenderer)) {
        cout << "Failed to load background image!" << endl;
        success = false;
    }
    return success;
}

void close() {
    // Free loaded images
    gBackground.Free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void process() {
    GameMap game_map;
    game_map.LoadMap((char*)MAP.c_str());
    game_map.LoadTiles(gRenderer);

    character player;
    player.LoadImg(PLAYER_IDLE, gRenderer);
    player.set_clips();

    bool quit = false;

    vector<threat*> list_threats = game_map.GetThreatList(gRenderer);
    vector<item*> list_coins = game_map.GetCoinList(gRenderer);

    Explosion explosion;
    if (!explosion.LoadImg(EXPLOSION_DIR, gRenderer)) {
        cout << "Failed to load explosion image!" << endl;
        quit = true;
    }
    explosion.set_clips();

    while(!quit) {
        fps_timer.start();
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }
            player.HandleInputAction(gEvent, gRenderer);
        }

        SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gRenderer);

        gBackground.Render(gRenderer, NULL);

        Map map_data = game_map.getMap();

        player.UpdateMap(map_data.start_x, map_data.start_y);
        player.DoPlayer(map_data);
        player.Render(gRenderer);

        game_map.setMap(map_data);
        game_map.DrawMap(gRenderer);

        // Render threats
        for (int i = 0; i < list_threats.size(); i++) {
            threat* p_threat = list_threats[i];
            if (p_threat != NULL) {
                p_threat->SetMap(map_data.start_x, map_data.start_y);
                p_threat->DoThreat(map_data);
                p_threat->Render(gRenderer);

                // Check collision
                if (utils::CheckCollision(player.GetTilePos(), p_threat->GetTilePos())) {
                    cout << "Collision detected!" << endl;
                    for (int i = 0; i < EXPLOSION_FRAME_NUMBER; i++) {
                        explosion.set_frame(i);
                        explosion.SetRect(player.GetRectFrame().x, player.GetRectFrame().y);
                        explosion.Render(gRenderer);
                    }

                    p_threat->Free();
                    list_threats.erase(list_threats.begin() + i);
                    player.SetStatus(character::MoveType::DEAD);
                }
            }
        }

        // Render item
        for (int i = 0; i < list_coins.size(); i++) {
            item* p_coin = list_coins[i];
            if (p_coin != NULL) {
                p_coin->SetMap(map_data.start_x, map_data.start_y);
                p_coin->Render(gRenderer);

                if (utils::CheckCollision(player.GetTilePos(), p_coin->GetTilePos())) {
                    p_coin->Free();
                    list_coins.erase(list_coins.begin() + i);
                    player.UpdateItems(COIN);
                }
            }
        }

//        if(player.CheckCollision(map_data)) {
//            if (map_data.object[player.GetTilePosY()][player.GetTilePosX()] == TRAP) {
//                cout << "Collision detected!" << endl;
//                for (int i = 0; i < EXPLOSION_FRAME_NUMBER; i++) {
//                    explosion.set_frame(i);
//                    explosion.SetRect(player.GetRectFrame().x, player.GetRectFrame().y);
//                    explosion.Render(gRenderer);
//                }
//                int index = game_map.GetThreatIndex({player.GetTilePosX(), player.GetTilePosY()});
//                list_threats[index]->Free();
//                list_threats.erase(list_threats.begin() + index);
//                player.SetStatus(character::MoveType::DEAD);
//            }
//            else if (map_data.object[player.GetTilePosY()][player.GetTilePosX()] == COIN) {
//                int index = game_map.GetCoinIndex({player.GetTilePosX(), player.GetTilePosY()});
//                list_coins[index]->Free();
//                list_coins.erase(list_coins.begin() + index);
//                player.UpdateItems(COIN);
//
//            }
//        }

        SDL_RenderPresent(gRenderer);

        int real_time = fps_timer.get_ticks();
        int frame_time = 1000 / FRAME_PER_SECOND;
        if (real_time < frame_time) {
            SDL_Delay(frame_time - real_time);
        }
    }
}
