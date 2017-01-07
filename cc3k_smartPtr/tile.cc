#include "tile.h"
using namespace std;


Tile::Tile(int x, int y, int chamberIndex): Object{x, y}, chamberIndex{chamberIndex} {
  symbol = '.';
  name = "tile";
}

int Tile::chamberNum() { return chamberIndex; }

bool Tile::isOccupied() { return occupied; }

void Tile::putObject(Object *obj) {
  ob = obj;
  symbol = obj->getSymbol();
  occupied = true;
}


void Tile::emptied() {
  ob = nullptr;
  occupied = false;
  symbol = '.';
}

void Tile::addNeighbor(string direction, Tile *t) {
  pair<string, Tile *> item;
  item.first = direction;
  item.second = t;
  neighbor.emplace_back(item);
}

unsigned int Tile::neighborSize() { return neighbor.size(); }

Tile *Tile::getNeighbor(int index) {
  return neighbor.at(index).second;
}

Object *Tile::item() {
  return ob;
}

Tile::~Tile() {}
