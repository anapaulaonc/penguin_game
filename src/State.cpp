#include "State.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include <iostream>
# define PI 3.14159265358979323846

State::State(): bg(*new GameObject(), "assets/img/ocean.jpg"){
    //Inicializando quitRequested
    this->quitRequested = false;
    this->LoadAssets();
  
    this->music.Play();
    // Instancia Sprite 
}

//Esvazia o array de objetos
State::~State(){
    this->objectArray.clear();
}

void State::LoadAssets(){
    //Inicializar os assets
    GameObject* object = new GameObject();
    object->AddComponent(&this->bg);
    object->box.x = 0;
    object->box.y = 0;
    object->box.w = this->bg.GetWidth();
    object->box.h = this->bg.GetHeight();
    this->objectArray.emplace_back(object);
    this->music = *new Music("assets/audio/stageState.ogg");
    
} 

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200,  0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}


void State::Update(float dt){
    this->Input();
	//Percorre o vetor dos objetos dando update de depois testando se estao mortos
    for(vector<int>::size_type i = 0; i < this->objectArray.size(); i++){
        this->objectArray[i]->Update(dt);
        if(this->objectArray[i]->IsDead()){
        	this->objectArray.erase(this->objectArray.begin() + i);
        }
    }
}

//Chama Render de todos os objetos do array
void State::Render(){
    for(vector<int>::size_type i = 0; i < this->objectArray.size(); i++){
        this->objectArray[i]->Render();
    }
}


void State::AddObject(int mouseX, int mouseY){
	//Cria um gameobject (o inimigo)
    GameObject* object = new GameObject();
	//A imagem do pinguin
    Sprite* enemy = new Sprite(*object, "assets/img/penguinface.png");
    object->AddComponent(enemy);
	//Atribui uma posicao ao pinguin
    object->box.x = mouseX;
    object->box.y = mouseY;
	//Tamanho da sprint para a imagem ficar centrada nas coordenadas
    object->box.w = enemy->GetWidth();
    object->box.h = enemy->GetHeight();
	//Adiciona o component Sound que tem o audio do "boom"
    Sound* sound = new Sound(*object, "assets/audio/boom.wav");
    object->AddComponent(sound);
    this->objectArray.emplace_back(object);
    Face* face = new Face(*object);
    object->AddComponent(face);
}

bool State::QuitRequested(){
    return this->quitRequested;
}




