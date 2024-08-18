//
// Created by ADMIN on 8/18/2024.
//

#ifndef GAME_LTNC_TEXT_H
#define GAME_LTNC_TEXT_H

#include "utils.h"

class text {
public:
    text();
    ~text();

    enum TextColor {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        BLUE_TEXT = 3,
        GREEN_TEXT = 4
    };

    string GetText() const { return value; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void SetFont(TTF_Font* font) { this->font = font; }
    void SetText(const string& text) { value = text; }
    void SetColor(const int& type);
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
//    void SetPos(const int& x, const int& y);

    void RenderText(SDL_Renderer* screen,
                    const int& xp,
                    const int& yp,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

    bool LoadFromRenderedText(TTF_Font* font, SDL_Renderer* screen);

    void Free();

private:
    string value;
    SDL_Color color;
    TTF_Font* font;
    SDL_Texture* texture;

    int width, height;
};


#endif //GAME_LTNC_TEXT_H
