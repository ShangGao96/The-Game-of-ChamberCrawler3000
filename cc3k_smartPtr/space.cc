#include "space.h"

Space::Space(int x, int y): Object{x, y} {
  symbol = ' ';
  name = "space";
}

Space::~Space() {}
