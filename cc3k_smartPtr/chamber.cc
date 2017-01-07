#include "chamber.h"
#include "tile.h"

#include <iostream>
using namespace std;


Chamber::Chamber(int index): index{index} {}


void Chamber::addTile(Tile *t) {
  ++size;
  member.emplace_back(t);
}


int Chamber::getIndex() { return index; }


Chamber::~Chamber() {
  member.clear();
}


Tile *Chamber::getTile(int num) {
  return member.at(num);
}


int Chamber::getSize() { return size; }



void Chamber::addNeighbor(Tile *t) {
  int row = t->getY();
  int col = t->getX();
  for (int i = 0; i < getSize(); ++i) {
    Tile *tmp = member.at(i);
    if (tmp->getY() == row && tmp->getX() == col - 1) {
      t->addNeighbor("we", tmp);
    } else if (tmp->getY() == row && tmp->getX() == col + 1) {
      t->addNeighbor("ea", tmp);
    } else if (tmp->getY() == row - 1 && tmp->getX() == col) {
      t->addNeighbor("no", tmp);
    } else if (tmp->getY() == row + 1 && tmp->getX() == col) {
      t->addNeighbor("so", tmp);
    } else if (tmp->getY() == row - 1 && tmp->getX() == col - 1) {
      t->addNeighbor("nw", tmp); 
    } else if (tmp->getY() == row - 1 && tmp->getX() == col + 1) {
      t->addNeighbor("ne", tmp);
    } else if (tmp->getY() == row + 1 && tmp->getX() == col - 1) {
      t->addNeighbor("sw", tmp);
    } else if (tmp->getY() == row + 1 && tmp->getX() == col + 1) {
      t->addNeighbor("se", tmp);
    }
  }
}
