#ifndef GAME_H
#define GAME_H

#include <string>
#include "State.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#include <SDL2/SDL.h>

using namespace std;


class Game
{
public:
   ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& Getstate();
    static Game& GetInstance();
private:
    Game(string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

#endif // GAME_H

//Pessoa obj = new Pessoa("Ana");
//obj.getName();


