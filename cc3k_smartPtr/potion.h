#ifndef _POTION_H_
#define _POTION_H_

#include <string>
#include "object.h"

class Potion: public Object {
  bool found = false;
  std::string function;         // RH, BA, BD, PH, WA, WD
 public:
  Potion(int x, int y, std::string function);
  std::string getFunction();   // return the specific function of the potion
  ~Potion();

};

#endif
