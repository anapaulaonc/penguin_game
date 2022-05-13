#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "Game.h"
Game* Game::instance = nullptr;

#include "SDL_include.h"
#include <iostream>
#include <cstdlib>
#include <ctime>



Game& Game::GetInstance(){
    //verifica se o game ja não existe
    if(instance != nullptr){
        return *instance;
    }
    //Cria um novo game e atribui nome e dimensoes
    new Game("Penguin Game", 1024, 600);
    return *instance;
}

Game::Game(string title, int width, int height){
    //Verifica se não tem problema na logica
    if(instance != nullptr){
        cout << "Game ERROR! Tururu.." << endl;
        exit(505);
    }
    instance = this;

    //Inicia a biblioteca SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        cout << "Error inicando o SDL" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }

    //Inicia a biblioteca de imagens
     if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
        cout << "Error iniciando imagens" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }


    //Inicia a audio
    if(!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)){
        cout << "Error iniciando mixer" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
        cout << "Error iniciando audio" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }
    if(!(Mix_AllocateChannels(32))){
        cout << "Error alocando canais necessarios" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }

    //Cria a janela do jogo
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(this->window == nullptr){
        cout << "Error criando a janela" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }

    // Cria a renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if(this->renderer == nullptr){
        cout << "Error criando a renderer" << endl;
        cout << SDL_GetError() << endl;
        exit(505);
    }
    this->state = new State();

    
}

//Desfazendo as inicializacoes (ordem contraria da inicializacao)
Game::~Game(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::Getstate(){
    return *this->state;
}

//Retornando o membro renderer (para o Sprite)
SDL_Renderer* Game::GetRenderer(){
    return this->renderer;
}

//Criando o Game Loop
void Game::Run(){
float dt;
    while(!(this->state->QuitRequested())){
        this->state->Update(dt);
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(33);
    }
}