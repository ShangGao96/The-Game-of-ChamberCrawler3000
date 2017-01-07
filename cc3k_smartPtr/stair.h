#ifndef _STAIR_H_
#define _STAIR_H_

#include "object.h"

class Stair: public Object {
  int chamberIndex;
  Object *ob = nullptr;
 public:
  Stair(int x, int y, int chamberIndex);
  int chamberNum();
  void putObject(Object *obj);
  void emptied();
  ~Stair();
};

#endif
