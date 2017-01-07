#ifndef _DOOR_H_
#define _DOOR_H_

#include "object.h"


class Door: public Object {
  int chamberIndex;
  Object *ob = nullptr;
 public:
  Door(int x, int y, int chamberIndex);
  int chamberNum();
  void putObject(Object *obj);
  void emptied();
  ~Door();
};

#endif
