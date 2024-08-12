#include "header/utils.h"
#include "header/gameObject.h"
#include "header/map.h"
#include "header/character.h"
#include "header/timer.h"
#include "header/threat.h"

bool initSDL();

gameObject gBackground;
bool loadBackground();

// Implement timer (fps)
timer fps_timer;

void close();
void process();
vector <threat*> MakeThreatsList();
vector <coin*> MakeCoinsList(GameMap &game_map);

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
    player.LoadImg(PLAYER_RIGHT, gRenderer);
    player.set_clips();

//    vector<threat*> list_threats = MakeThreatsList();
    vector<coin*> list_coins = MakeCoinsList(game_map);

    bool quit = false;
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

//        // Render threats
//        for (int i = 0; i < list_threats.size(); i++) {
//            threat* p_threat = list_threats.at(i);
//            if (p_threat != NULL) {
//                p_threat->SetMap(map_data.start_x, map_data.start_y);
////                p_threat->ImpMoveType(gRenderer);
//                p_threat->DoThreat(map_data);
//                p_threat->Render(gRenderer);
//
//                // Check collision
//                if (utils::CheckCollision(player.GetRectFrame(), p_threat->GetRect())) {
//                    cout << "Collision!" << endl;
//                }
//            }
//        }


        // Render coin
        for (int i = 0; i < list_coins.size(); i++) {
            coin* p_coin = list_coins[i];
            if (p_coin != NULL) {
                p_coin->SetMap(map_data.start_x, map_data.start_y);
                p_coin->Render(gRenderer);

                if (utils::CheckCollision(player.GetRectFrame(), p_coin->GetRect())) {
                    p_coin->Free();
                    list_coins.erase(list_coins.begin() + i);
                }
            }
        }

        SDL_RenderPresent(gRenderer);

        int real_time = fps_timer.get_ticks();
        int frame_time = 1000 / FRAME_PER_SECOND;
        if (real_time < frame_time) {
            SDL_Delay(frame_time - real_time);
        }
    }
}

vector <threat*> MakeThreatsList() {
    vector <threat*> list_threats;

//    threat* dynamic_threat = new threat[20];
//    for (int i = 0; i < 20; i++) {
//        threat* p_threat = (dynamic_threat + i);
//        if (p_threat == NULL) {
//            cout << "Memory allocation failed!" << endl;
//            return list_threats;
//        } else {
//            p_threat->LoadImg(THREAT, gRenderer);  // Load image threat left?
//            p_threat->set_clips();
//            p_threat->set_type_move(threat::MoveType::MOVE_THREAT);
//
//            p_threat->setX_pos(500 + i * 500);
//            p_threat->setY_pos(200);
//
//            int pos1 = p_threat->getX_pos() - 60;
//            int pos2 = p_threat->getX_pos() + 60;
//            p_threat->setAnimationPos(pos1, pos2);
//
//            list_threats.push_back(p_threat);
//        }
//    }

    threat* threat_obj = new threat[20];
    for (int i = 0; i < 20; i++) {
        threat* p_threat = (threat_obj + i);
        if (p_threat == NULL) {
            cout << "Memory allocation failed!" << endl;
            return list_threats;
        } else {
            p_threat->LoadImg(THREAT, gRenderer);
            p_threat->set_clips();
            p_threat->setX_pos(700 + i * 1200);
            p_threat->setY_pos(250);
            p_threat->set_type_move(threat::MoveType::STATIC_THREAT);
            p_threat->setInputLeft(0);

            list_threats.push_back(p_threat);
        }
    }

    return list_threats;
}

vector<coin*> MakeCoinsList(GameMap &game_map) {
    vector <coin*> list_coins;
    vector <vector<int>> coin_list = game_map.GetCoinList();

    for (int i = 0; i < coin_list.size(); i++) {
        coin* p_coin = new coin();
        p_coin->LoadImg(PROJECT_SOURCE_DIR + "res/coin.png", gRenderer);
        p_coin->set_clips();
        p_coin->setX_pos(coin_list[i][0]);
        p_coin->setY_pos(coin_list[i][1]);
        p_coin->setInputLeft(0);

        list_coins.push_back(p_coin);
    }

    return list_coins;
}