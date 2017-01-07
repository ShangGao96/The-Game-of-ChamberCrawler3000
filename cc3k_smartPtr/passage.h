#ifndef _PASSAGE_H_
#define _PASSAGE_H_

#include "object.h"

class Passage: public Object {
  Object *ob = nullptr;
 public:
  Passage(int x, int y);
  void putObject(Object *obj);
  void emptied();
  ~Passage();
};

#endif
