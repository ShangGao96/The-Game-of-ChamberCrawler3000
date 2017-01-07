#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include <string>

class Player;
class Floor;
class Object;

class TextDisplay{
  std::vector<std::vector<char>> theDisplay;   // a two dimention vector which record all the symbol of the floor
  Floor *thefloor;                             // a pointer to the floor object
  std::string race;
  int hp;
  int atk;
  int def;
  float gold;
  int level;
  std::string action;                           // the message displayed on the screen
 
 public:
  TextDisplay(std::string race, int hp, int atk, int def, float gold, int level, std::string action);
  void init();
  void notify(Object *ob);                      // the object (ob) on the floor notify the TextDisplay when their state is changed
  void playernotify(Player *p);                 // player notify the TextDisplay when its state is changed
                                                // i.e. HP, Atk, Def, Gold change
  void addAction(std::string act);              // add the action to the screen
  ~TextDisplay();
  void setFloor(Floor *f);
  void clearAction();                           // reset the action message
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};



std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
