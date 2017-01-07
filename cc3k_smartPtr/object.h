#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
class TextDisplay;

class Object {
 protected:
  TextDisplay *td = nullptr;
  int x;       // x coordination
  int y;       // y coordination
  char symbol; // the symbol to represent the Object
  std::string name; // the name of the object
  Object(const Object &other);
 public:
  Object(int x, int y); // ctor
  void setTextDisplay(TextDisplay *text);
  int getX() const;
  int getY() const;
  void setX(int xc);
  void setY(int yc);
  std::string getName() const;
  char getSymbol() const;
  virtual ~Object()=0;
};

#endif
