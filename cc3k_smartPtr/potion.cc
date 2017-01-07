#include "potion.h"
using namespace std;

Potion::Potion(int x, int y, string function): Object{x, y}, function {function} {
  symbol = 'P';
  name = "potion";
}

string Potion::getFunction() { return function; }

Potion::~Potion(){}
