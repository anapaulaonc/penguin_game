#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
using namespace std;

class Sprite : public Component{
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, string file);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(string type);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif