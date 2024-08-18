//
// Created by ADMIN on 8/18/2024.
//

#ifndef GAME_LTNC_BUTTON_H
#define GAME_LTNC_BUTTON_H


#include "utils.h"

class Button {
public:
    Button();
    ~Button();

    // Set position of the button
    void setPosition(int x, int y);

    // Load button image
    bool loadImage(std::string path, SDL_Renderer* renderer);

    // Render the button
    void render(SDL_Renderer* renderer);

    // Handle mouse events
    bool handleEvent(SDL_Event* e);
    bool isHover(SDL_Event* e);

private:
    SDL_Point position;
    SDL_Texture* texture;
    SDL_Rect rect;
};


#endif //GAME_LTNC_BUTTON_H
