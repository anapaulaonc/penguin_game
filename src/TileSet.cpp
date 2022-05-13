#include "TileSet.h"
#include "Sprite.h"
#include "GameObject.h"

#include <iostream>

//Abre o Spripe e seta as dimensoes dos tiles e as quantidades de colunas e linhas
TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*new GameObject()){
  tileSet.Open(file);
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  this->rows = tileSet.GetHeight() / tileHeight;
  this->columns = tileSet.GetWidth() / tileWidth;  
}

//Calcula e seta o setClip certo no sprite, e renderiza com base nas posicoes x e y
void TileSet::RenderTile(unsigned int index, float x, float y){
  //Checando se o indice e valido
  if (index > (unsigned int)(rows * columns)) return;
  int clipX = (index % columns * tileWidth), clipY = index / columns * tileHeight;
  tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
  tileSet.Render(x, y);
}

//Retornam as dimensoes dos tiles para usar no tilemap
int TileSet::GetTileHeight(){
  return this->tileHeight;
}
int TileSet::GetTileWidth(){
  return this->tileWidth;
}

TileSet::~TileSet(){

}