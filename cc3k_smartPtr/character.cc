#include "character.h"
#include <iostream>
using namespace std;


Character::Character(int x, int y): Object{x, y} {}

Character::Character(const Character &other):
     Object{other}, beginHP{other.beginHP}, beginAtk{other.beginAtk}, beginDef{other.beginDef}, curHP{other.curHP},
                       curAtk{other.curAtk}, curDef{other.curDef} {}

int Character::getHP() const { return curHP; }

int Character::getAtk() const { return curAtk; }

int Character::getDef() const { return curDef; }

bool Character::isLive() const { return live; }

Character::~Character() {}
