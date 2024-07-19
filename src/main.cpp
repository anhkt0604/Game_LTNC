#include "header/utils.h"
#include "header/gameObject.h"
#include "header/map.h"
#include "header/character.h"

bool init();

gameObject gBackground;
bool loadBackground();

void close();
void process();

int main(int argc, char* argv[]) {
    if (!init()) {
        return -1;
    }
    if (!loadBackground()) {
        return -1;
    }

    process();

    close();
    return 0;
}

bool init() {

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
    player.LoadImg(PROJECT_SOURCE_DIR + "res/player_right.png", gRenderer);
    player.set_clips();

    bool quit = false;
    while(!quit) {
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
        game_map.DrawMap(gRenderer);

        player.Render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }
}
