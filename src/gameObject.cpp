#include "header/gameObject.h"

gameObject::gameObject() {
    object = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

gameObject::~gameObject() {
    Free();
}

bool gameObject::LoadImg(const string &path, SDL_Renderer *screen, const int &r, const int &g, const int &b) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));
    object = SDL_CreateTextureFromSurface(screen, loadedSurface);
    if (object == NULL) {
        cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    rect.w = loadedSurface->w;
    rect.h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return object != NULL;
}

void gameObject::Render(SDL_Renderer *screen, const SDL_Rect *clip) {
    SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(screen, object, clip, &renderQuad);
}

void gameObject::Free() {
    if (object != NULL) {
        SDL_DestroyTexture(object);
        object = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
