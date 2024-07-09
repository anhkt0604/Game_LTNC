#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    } else {
        cout << "SDL initialized!" << endl;
    }

    // show blue screen and close by clicking the close button
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
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
