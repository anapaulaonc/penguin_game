#include "Face.h"
#include "Sound.h"
#include "GameObject.h"
#include <string>
#include <chrono>
#include <thread>
using namespace std;

//Seta valor inicial de hitpoints 
Face::Face(GameObject& associated) : Component(associated){
    this->hitpoints = 30;
}

//Reduz os hitpoints 
void Face::Damage(int damage){
    this->hitpoints -= damage;
    Sound* sound = (Sound*) this->associated.GetComponent("Sound");
    //Se os hitpoints ficar < ou = 0, chama o Requestdelete
    if(this->hitpoints <= 0 && !this->associated.IsDead()){
        this->associated.RequestDelete();
        //Play no sound de destruicao
        if(sound != nullptr){
            sound->Play();
            this_thread::sleep_for(1.8s);
            
        }
    }
}

void Face::Update(float dt){
//Deixar vazio
}

void Face::Render(){
//Deixar vazio
}

//Se o tipo for face retorna verdadeiro
bool Face::Is(string type){
    if(type == "Face"){
        return true;
    }
    else {
        return false;
    }
}