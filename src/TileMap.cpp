#include "TileMap.h"
#include <fstream>
#include <iostream>

//Chama o load e seta o tileset
TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet)  : Component(associated){
  this->Load(file);
  this->SetTileSet(tileSet);
}

//Carregar um arquivo de mapa que e uma matriz
void TileMap::Load(string file){
  ifstream stream(file, ios::in);
  if (!stream.is_open()){
    cout << "Error loading file " << file << endl;
    exit(1);
  }
  //Ps: tiles  vazios  são  representados por 0
  char c;
  stream >> mapWidth >> c >> mapHeight >> c >> mapDepth >> c;

  int in;
  while (stream >> in){
    tileMatrix.push_back(in - 1);
    stream >> c;
  }
}

//Troca o tileSet que esta sendoo usado
void TileMap::SetTileSet(TileSet* tileSet){
  this->tileSet = tileSet;
}

//Retorna  uma  referência  ao  elemento  [x][y][z] de  tileMatrix
int& TileMap::At(int x, int y, int z){
  int idx = z * mapWidth * mapHeight + y * mapWidth + x;
  return tileMatrix[idx];
}

//Renderiza as camadas do mapa
void TileMap::Render(){
  // i = layer
  for (int i = 0; i < mapDepth; i++){
    RenderLayer(i, 0, 0);
  }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
  for (int y = 0; y < mapHeight; y++){
    for (int x = 0; x < mapWidth; x++){
      int xPos = x * tileSet->GetTileWidth() - cameraX;
      int yPos = y * tileSet->GetTileHeight() - cameraY;
      tileSet->RenderTile(At(x, y, layer), xPos, yPos);
    }
  }
}

//Retornam as dimensoes do mapa
int TileMap::GetWidth(){
  return this->mapWidth;
}
int TileMap::GetHeight(){
  return this->mapHeight;
}
int TileMap::GetDepth(){
  return this->mapDepth;
}


bool TileMap::Is(string type){
  return "TileMap" == type;
}


TileMap::~TileMap(){
}

void TileMap::Update(float dt){
}