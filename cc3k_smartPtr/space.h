#ifndef _SPACE_H_
#define _SPACE_H_

#include "object.h"

class Space: public Object {
 public:
  Space(int x, int y);
  ~Space();
};
#endif
