#include "character.h"
#include "object.h"
using namespace std;

Object::Object(int x, int y): x{x}, y{y} {}


Object::Object(const Object &other): 
   x{other.x}, y{other.y}, symbol{other.symbol}, name{other.name} {}


int Object::getX() const { return x; }


int Object::getY() const { return y; }


void Object::setX(int xc) { x = xc; }


void Object::setY(int yc) { y = yc; }


string Object::getName() const { return name; }


char Object::getSymbol() const { return symbol; }


void Object::setTextDisplay(TextDisplay *text) {
	td = text;
}


Object::~Object() {}
