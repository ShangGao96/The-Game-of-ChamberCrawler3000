#include "door.h"

Door::Door(int x, int y, int chamberIndex): Object{x, y}, chamberIndex{chamberIndex} {
  symbol = '+';
  name = "door";
}

int Door::chamberNum() { return chamberIndex; }

void Door::putObject(Object *obj) {
  ob = obj;
  symbol = obj->getSymbol();
}


void Door::emptied() {
  ob = nullptr;
  symbol = '+';
}

Door::~Door() {}
