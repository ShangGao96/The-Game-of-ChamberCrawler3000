#include "stair.h"
using namespace std;

Stair::Stair(int x, int y, int chamberIndex): Object{x, y}, chamberIndex{chamberIndex} {
  symbol = '\\';
  name = "stair";
}

int Stair::chamberNum() { return chamberIndex; }


void Stair::putObject(Object *obj) {
	ob = obj;
	symbol = obj->getSymbol();
}

void Stair::emptied() {
  ob = nullptr;
  symbol = '\\';
}

Stair::~Stair() {}
