#include <SDL.h>
#include <SDL_image.h>
#include "utils/utils.h"

const string PROJECT_SOURCE_DIR = getPath();

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    } else {
        cout << "SDL initialized!" << endl;
    }

    SDL_Window* window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    // Set Window Icon
    SDL_Surface *icon = IMG_Load((PROJECT_SOURCE_DIR + "res/icon.png").c_str());
    if (icon == NULL) {
        cout << "Icon could not be loaded! SDL_Error: " << SDL_GetError() << endl;
    } else {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    } else {
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        } else {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // white color
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
            }
            SDL_DestroyRenderer(renderer);
        }
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;

}

