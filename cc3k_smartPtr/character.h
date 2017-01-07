#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

class Character: public Object {
 protected:
  int beginHP, beginAtk, beginDef;
  int curHP, curAtk, curDef;
  bool live = true;            // true if the HP of the Character is larger than 0
  Character(int x, int y);
  Character(const Character &other);
 public:
  bool isLive() const;
  int getHP() const;
  int getAtk() const;
  int getDef() const;
  ~Character();
};
#endif
