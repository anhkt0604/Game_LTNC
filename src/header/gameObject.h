#ifndef GAME_LTNC_GAMEOBJECT_H
#define GAME_LTNC_GAMEOBJECT_H

#include "utils.h"

using namespace std;

class gameObject {
public:
    gameObject();
    ~gameObject();
    inline void SetRect(const int& x, const int& y) { rect.x = x; rect.y = y; }
    int GetWidth() const { return rect.w; }
    int GetHeight() const { return rect.h; }
    SDL_Rect GetRect() const { return rect; }
    SDL_Texture* GetTexture() const { return object; }

    virtual bool LoadImg(const string& path, SDL_Renderer* screen,
                         const int& r = COLOR_KEY_R, const int& g = COLOR_KEY_G, const int& b = COLOR_KEY_B);
    void Render(SDL_Renderer* screen, const SDL_Rect* clip = NULL);
    void Free();

protected:
    SDL_Texture* object;
    SDL_Rect rect;
};

#endif //GAME_LTNC_GAMEOBJECT_H
