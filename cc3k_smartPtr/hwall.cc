#include "hwall.h"

Hwall::Hwall(int x, int y): Object{x, y} {
  symbol = '-';
  name = "horizontal wall";
}

Hwall::~Hwall() {}
