//
// Created by ADMIN on 8/18/2024.
//

#include "header/Button.h"

Button::Button() {
    texture = NULL;
    position.x = 0;
    position.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Button::~Button() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Button::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

bool Button::loadImage(std::string path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    rect.w = loadedSurface->w;
    rect.h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return true;
}

void Button::render(SDL_Renderer* renderer) {
    SDL_Rect renderQuad = {position.x, position.y, rect.w, rect.h};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

bool Button::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;
        if (x < position.x || x > position.x + rect.w || y < position.y || y > position.y + rect.h) {
            inside = false;
        }

        if (inside) {
            if (e->type == SDL_MOUSEBUTTONDOWN) {
                return true; // Button clicked
            }
        }
    }
    return false;
}

bool Button::isHover(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;
        if (x < position.x || x > position.x + rect.w || y < position.y || y > position.y + rect.h) {
            inside = false;
        }

        if (inside) {
            return true; // Mouse hover
        }
    }
    return false;
}