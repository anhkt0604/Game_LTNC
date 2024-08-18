#include "header/utils.h"
#include "header/gameObject.h"
#include "header/map.h"
#include "header/character.h"
#include "header/timer.h"
#include "header/threat.h"
#include "header/explosion.h"
#include "header/text.h"
#include "header/Image.h"
#include "header/Button.h"

bool initSDL();

gameObject gBackground;
bool loadBackground();

int result_score;
bool win = false;

gameObject menuBackground;
gameObject HowToPlay;
Button playButton;
Button exitButton;
Button Q_button;
Button OK_button;
bool loadMenu();
bool loadHowToPlay();

gameObject resultWin;
gameObject resultLose;
Button restartButton;
bool loadResult();

// Implement timer (fps)
timer fps_timer;

void close();
void process();
void showMenu();
void showResult();
void showHowToPlay();

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return -1;
    }

    if (!loadBackground() || !loadMenu() || !loadResult() || !loadHowToPlay()) {
        return -1;
    }

    showMenu();
//    showResult();

//    process();
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

    // Init SDL_TTF
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }

    default_font = TTF_OpenFont((PROJECT_SOURCE_DIR + "res/font/JetBrainsMono-Bold.ttf").c_str(), 25);
    if (default_font == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }

    result_font = TTF_OpenFont((PROJECT_SOURCE_DIR + "res/font/JetBrainsMono-ExtraBold.ttf").c_str(), 40);
    if (result_font == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }

    // init SDL_Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    coin_sound = Mix_LoadWAV((COIN_SOUND).c_str());
    explosion_sound = Mix_LoadWAV((EXPLOSION_SOUND).c_str());
    if (coin_sound == NULL || explosion_sound == NULL) {
        cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
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

bool loadMenu() {
    bool success = true;
    if (!menuBackground.LoadImg(MENU_BACKGROUND, gRenderer)) {
        cout << "Failed to load background image!" << endl;
        success = false;
    }

    if (!playButton.loadImage(PROJECT_SOURCE_DIR + "res/play_button.png", gRenderer)) {
        cout << "Failed to load start button image!" << endl;
        success = false;
    } else {
        playButton.setPosition(520,374);
    }

    if (!exitButton.loadImage(PROJECT_SOURCE_DIR + "res/exit_button.png", gRenderer)) {
        cout << "Failed to load exit button image!" << endl;
        success = false;
    } else {
        exitButton.setPosition(520, 374 + 90);
    }

    if (!Q_button.loadImage(PROJECT_SOURCE_DIR + "res/Q_button.png", gRenderer)) {
        cout << "Failed to load Q button image!" << endl;
        success = false;
    } else {
        Q_button.setPosition(1200, 640 - 80);
    }


    return success;
}

bool loadHowToPlay() {
    bool success = true;
    if (!HowToPlay.LoadImg(PROJECT_SOURCE_DIR + "res/tutorial.png", gRenderer)) {
        cout << "Failed to load how to play image!" << endl;
        success = false;
    }

    if (!OK_button.loadImage(PROJECT_SOURCE_DIR + "res/OK_button.png", gRenderer)) {
        cout << "Failed to load OK button image!" << endl;
        success = false;
    } else {
        OK_button.setPosition(520, 374 + 140);
    }

    return success;
}

bool loadResult() {
    bool success = true;
    if (!resultWin.LoadImg(PROJECT_SOURCE_DIR + "res/result_win.png", gRenderer)) {
        cout << "Failed to load result screen image!" << endl;
        success = false;
    }
    if(!resultLose.LoadImg(PROJECT_SOURCE_DIR + "res/result_lose.png", gRenderer)) {
        cout << "Failed to load result screen image!" << endl;
        success = false;
    }

    if (!restartButton.loadImage(PROJECT_SOURCE_DIR + "res/restart_button.png", gRenderer)) {
        cout << "Failed to load restart button image!" << endl;
        success = false;
    } else {
        restartButton.setPosition(520,374);
    }

    return success;
}

void close() {
    // Free loaded images
    gBackground.Free();
    menuBackground.Free();
    resultWin.Free();
    resultLose.Free();

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
    bool quit = false;
    win = false;

    GameMap game_map;
    game_map.LoadMap((char*)MAP.c_str());
    game_map.LoadTiles(gRenderer);

    character player;
    player.LoadImg(PLAYER_IDLE, gRenderer);
    player.set_clips();

    vector<threat*> list_threats = game_map.GetThreatList(gRenderer);
    vector<item*> list_coins = game_map.GetCoinList(gRenderer);

    item* door = game_map.GetDoor(gRenderer);
    item* key = game_map.GetKey(gRenderer);

    Explosion explosion;
    if (!explosion.LoadImg(EXPLOSION_DIR, gRenderer)) {
        cout << "Failed to load explosion image!" << endl;
        quit = true;
    }
    explosion.set_clips();

    // Text
    text scoreText, chanceText, notificationText;
    scoreText.SetColor(text::BLACK_TEXT);
    chanceText.SetColor(text::BLACK_TEXT);
    notificationText.SetColor(text::RED_TEXT);

    Image CoinImage(PROJECT_SOURCE_DIR + "res/coin_image.png", gRenderer);
    Image ChanceImage(PROJECT_SOURCE_DIR + "res/heart.png", gRenderer);


    while(!quit) {
        fps_timer.start();
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                close();
            }
            player.HandleInputAction(gEvent, gRenderer);
        }

        if (player.isDead()) {
            cout << "Game Over!" << endl;
            result_score = player.GetScore();
            win = false;

            showResult();
            quit = true;
        }

        SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gRenderer);

        gBackground.Render(gRenderer, NULL);

        Map map_data = game_map.getMap();

        // Render door
        door->SetMap(map_data.start_x, map_data.start_y);
        door->Render(gRenderer);
        if (utils::CheckCollision(player.GetTilePos(), door->GetTilePos())) {
            if (player.GetKey()) {
                cout << "You win!" << endl;
                result_score = player.GetScore();
                win = true;

                showResult();
                quit = true;
            } else {
                cout << "You need a key to open the door!" << endl;
                notificationText.SetText("You need a key to open the door!");
                notificationText.LoadFromRenderedText(default_font, gRenderer);
                notificationText.RenderText(gRenderer, SCREEN_WIDTH / 2 - notificationText.GetWidth() / 2, 20);
            }
        }

        // Render key
        key->SetMap(map_data.start_x, map_data.start_y);
        key->Render(gRenderer);
        if (utils::CheckCollision(player.GetTilePos(), key->GetTilePos())) {
            key->Free();
            player.SetKey(true);
        }

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
                p_threat->Render(gRenderer);

                // Check collision
                if (utils::CheckCollision(player.GetTilePos(), p_threat->GetTilePos())) {
                    cout << "Collision detected!" << endl;
                    Mix_PlayChannel(-1, explosion_sound, 0);
                    for (int i = 0; i < EXPLOSION_FRAME_NUMBER; i++) {
                        explosion.set_frame(i);
                        explosion.SetRect(player.GetRectFrame().x, player.GetRectFrame().y);
                        explosion.Render(gRenderer);
                    }

                    p_threat->Free();
                    list_threats.erase(list_threats.begin() + i);
                    player.SetStatus(character::MoveType::DEAD);
                    player.useHeart();
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
                    cout << "Collision detected!" << endl;
                    Mix_PlayChannel(-1, coin_sound, 0);
                    p_coin->Free();
                    list_coins.erase(list_coins.begin() + i);
                    player.UpdateItems(COIN);
                }
            }
        }


        // Render text
        chanceText.SetText("Chance:");
        chanceText.LoadFromRenderedText(default_font, gRenderer);
        chanceText.RenderText(gRenderer, 30, 20);
        for (int i = 0; i < player.GetHeart(); i++) {
            ChanceImage.render(30 + chanceText.GetWidth() + 10 + i * 30, 24, 25, 25);
        }

        scoreText.SetText("Score: " + to_string(player.GetScore()));
        scoreText.LoadFromRenderedText(default_font, gRenderer);
        scoreText.RenderText(gRenderer, SCREEN_WIDTH - scoreText.GetWidth() - 60, 20);
        if (player.GetScore() >= 10) {
            CoinImage.render(SCREEN_WIDTH - scoreText.GetWidth() + 85, 24, 25, 25);
        } else {
            CoinImage.render(SCREEN_WIDTH - scoreText.GetWidth() + 70, 24, 25, 25);
        }

        SDL_RenderPresent(gRenderer);

        int real_time = fps_timer.get_ticks();
        int frame_time = 1000 / FRAME_PER_SECOND;
        if (real_time < frame_time) {
            SDL_Delay(frame_time - real_time);
        }
    }
}

void showMenu() {
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }

            if (Q_button.handleEvent(&gEvent)) {
                showHowToPlay();
                quit = true;
            }

            // Handle button events
            if (playButton.handleEvent(&gEvent)) {
                process();
                quit = true;
            }

            if (exitButton.handleEvent(&gEvent)) {
                quit = true;
            }

            if (playButton.isHover(&gEvent)) {
                // button zoom out
                playButton.loadImage(PROJECT_SOURCE_DIR + "res/play_button_hover.png", gRenderer);
            } else {
                // button zoom in
                playButton.loadImage(PROJECT_SOURCE_DIR + "res/play_button.png", gRenderer);
            }

            if (exitButton.isHover(&gEvent)) {
                // button zoom out
                exitButton.loadImage(PROJECT_SOURCE_DIR + "res/exit_button_hover.png", gRenderer);
            } else {
                // button zoom in
                exitButton.loadImage(PROJECT_SOURCE_DIR + "res/exit_button.png", gRenderer);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu background
        menuBackground.Render(gRenderer, NULL);

        // Render start button
        playButton.render(gRenderer);

        // Render exit button
        exitButton.render(gRenderer);

        // Render Q button
        Q_button.render(gRenderer);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

void showResult() {
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }

            // Handle button events
            if (restartButton.handleEvent(&gEvent)) {
                process();
            }

            if (exitButton.handleEvent(&gEvent)) {
                quit = true;
            }

            if (restartButton.isHover(&gEvent)) {
                // button zoom out
                restartButton.loadImage(PROJECT_SOURCE_DIR + "res/restart_button_hover.png", gRenderer);
            } else {
                // button zoom in
                restartButton.loadImage(PROJECT_SOURCE_DIR + "res/restart_button.png", gRenderer);
            }

            if (exitButton.isHover(&gEvent)) {
                // button zoom out
                exitButton.loadImage(PROJECT_SOURCE_DIR + "res/exit_button_hover.png", gRenderer);
            } else {
                // button zoom in
                exitButton.loadImage(PROJECT_SOURCE_DIR + "res/exit_button.png", gRenderer);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render result screen
        if (win) {
            resultWin.Render(gRenderer, NULL);
        } else {
            resultLose.Render(gRenderer, NULL);
        }

        // Render restart button
        restartButton.render(gRenderer);

        // Render exit button
        exitButton.render(gRenderer);


        // Render score
        text scoreText;
        scoreText.SetColor(text::BLACK_TEXT);
        scoreText.SetText("Your score: " + to_string(result_score));
        scoreText.LoadFromRenderedText(result_font, gRenderer);
        scoreText.RenderText(gRenderer, SCREEN_WIDTH / 2 - scoreText.GetWidth() / 2 - 10, 250);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

void showHowToPlay() {
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }

            // Handle button events

            if (OK_button.handleEvent(&gEvent)) {
                showMenu();
                quit = true;
            }


            if (OK_button.isHover(&gEvent)) {
                // button zoom out
                OK_button.loadImage(PROJECT_SOURCE_DIR + "res/OK_button_hover.png", gRenderer);
            } else {
                // button zoom in
                OK_button.loadImage(PROJECT_SOURCE_DIR + "res/OK_button.png", gRenderer);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render how to play screen
        HowToPlay.Render(gRenderer, NULL);

        // Render OK button
        OK_button.render(gRenderer);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}