//
// Created by ADMIN on 8/18/2024.
//

#ifndef GAME_LTNC_IMAGE_H
#define GAME_LTNC_IMAGE_H

#include "utils.h"

class Image {
public:
    Image() : texture(nullptr), renderer(nullptr), width(0), height(0) {}

    Image(const std::string& filePath, SDL_Renderer* renderer)
            : texture(nullptr), renderer(renderer) {
        // Load image from specified path
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (surface == nullptr) {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
            return;
        }

        // Create texture from surface
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }

        // Get image dimensions
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        // Free the loaded surface
        SDL_FreeSurface(surface);
    }

    ~Image() {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }

    void render(int x, int y, int w = -1, int h = -1) {
        if (texture != nullptr) {

            if (w == -1) w = width;
            if (h == -1) h = height;

            SDL_Rect dstRect = { x, y, w, h };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        }
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width, height;
};



#endif //GAME_LTNC_IMAGE_H
