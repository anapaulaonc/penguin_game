#ifndef _STATE_H
#define _STATE_H
#include <string>

#include "Sprite.h"
#include "Music.h"
using namespace std;

class State{
    public: 
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};

#endif