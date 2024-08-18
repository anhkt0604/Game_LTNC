//
// Created by ADMIN on 8/18/2024.
//

#include "header/text.h"

text::text() {
    color.r = 255;
    color.g = 255;
    color.b = 255;
    texture = NULL;
}

text::~text() {
    Free();
}

void text::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void text::SetColor(const int &type) {
    switch (type) {
        case RED_TEXT:
            color = {227, 54, 54};
            break;
        case WHITE_TEXT:
            color = {255, 255, 255};
            break;
        case BLACK_TEXT:
            color = {0, 0, 0};
            break;
        case BLUE_TEXT:
            color = {0, 0, 255};
            break;
    }
}

void text::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    color = {red, green, blue};
}

void text::RenderText(SDL_Renderer *screen, const int &xp, const int &yp,
                      SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {

    SDL_Rect renderQuad = {xp, yp, width, height};
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}


bool text::LoadFromRenderedText(TTF_Font* font, SDL_Renderer *screen) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, value.c_str(), color);
    if (textSurface) {
        texture = SDL_CreateTextureFromSurface(screen, textSurface);

        if (texture == NULL) {
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
    else {
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    return texture != NULL;
}

