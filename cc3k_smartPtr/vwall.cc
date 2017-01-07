#include "vwall.h"

Vwall::Vwall(int x, int y) :Object{x, y} {
  symbol = '|';
  name = "vertical wall";
}

Vwall::~Vwall() {}
