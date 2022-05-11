#include "Sound.h"
#include "GameObject.h"
#include <string>
#include <iostream>

using namespace std;

//Atribui associated ao atributo que tem o mesmo nome
Sound::Sound(GameObject& associated) : Component(associated) {
    //nulltrp a chunk
    this->chunk = nullptr;
}

//Chama o open
Sound::Sound(GameObject& associated, string file) : Component(associated){
    Open(file);
}

//Mixer retornara o numero do primeiro canal vazio que ela encontrar ( se nenhum canal tiver vazio ela não toca)
void Sound::Play(int times){
    this->channel = Mix_PlayChannel(-1, this->chunk, times);

}

//Se chunk for diferente de nulltrp para o canal que o chunk correspondente ta tocando 
void Sound::Stop(){
    if(this->chunk != nullptr){
        Mix_HaltChannel(this->channel);
    }
}

//Abre o arquivo MIX_Load
void Sound::Open(string file){
    Mix_Chunk* aux_chunk = Mix_LoadWAV(file.c_str());
    //Abertura falhar
    if(aux_chunk == nullptr){
        cout << "Error iniciando som" << endl;
        cout << SDL_GetError() << endl;
        exit(1);
    }
    this->chunk = aux_chunk;
}

//Se chunk for diferente de nulltrp, chama o Halt e desaloca o som 
Sound::~Sound(){
    if(this->chunk != nullptr){
        this->Stop();
        Mix_FreeChunk(this->chunk);
    }
}

void Sound::Update(float dt){}

void Sound::Render(){}

bool Sound::Is(string type){
    if(type == "Sound"){
        return true;
    }
    return false;
}