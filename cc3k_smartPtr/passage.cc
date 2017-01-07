#include "passage.h"

Passage::Passage(int x, int y): Object{x, y} {
  symbol = '#';
  name = "passage";
}

void Passage::putObject(Object *obj) {
  ob = obj;
  symbol = obj->getSymbol();
}


void Passage::emptied() {
  ob = nullptr;
  symbol = '#';
}

Passage::~Passage() {}
