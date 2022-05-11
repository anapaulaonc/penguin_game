#include "GameObject.h"
#include "Component.h"
#include <memory>
using namespace std;

//Certifica que isDead está setado como falso 
GameObject::GameObject(){
    this->isDead = false;
}

//usei clear para limpar o vetor de components ao inves de dar delete em cada espaco do vetor
GameObject::~GameObject(){
    this->components.clear();
}

//percorre o vetor de components chamando o update em cada um deles
void GameObject::Update(float dt){
    for (vector<int>::size_type i = 0; i < this->components.size(); i++){
        this->components[i]->Update(dt);
    }    
}

//percorre o vetor de components chamando o render em cada um deles
void GameObject::Render(){
    for (vector<int>::size_type i = 0; i < this->components.size(); i++){
        this->components[i]->Render();
    }    
}

//retorna o isDead
bool GameObject::IsDead(){
    return this->isDead;
}

//atribui isDead como verdadeiro
void GameObject::RequestDelete(){
     this->isDead = true;
}

//Adiciona o Component ao vetor de componentes
void GameObject::AddComponent(Component* cpt){
    this->components.emplace_back(cpt);
}

//Se o component estiver no vetor de components, ira remove-lo
void GameObject::RemoveComponent(Component* cpt){
    for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
        if(this->components[i].get() == cpt){
        this->components.erase(this->components.begin() + i);
        }
    }
}

//Retorna um ponteiro para o componente  do tipo que tiver adicionado nesse oobjetivo
Component* GameObject::GetComponent(string type){
    for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
        if(this->components[i]->Is(type)){
        return this->components[i].get();
        }
    }
    //se o componente nao existir
    return nullptr;
}
