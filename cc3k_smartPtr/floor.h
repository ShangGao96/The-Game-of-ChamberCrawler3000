#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <vector>
#include <string>
#include <memory>

class Chamber;
class Object;
class Player;
class Enemy;
class Potion;
class Treasure;
class Tile;
class Stair;
class TextDisplay;

class Floor {
  int level = 1;
  int numEnemy = 20;
  bool fileProvided = false;          // true if a file that specifies the layout of the floors is provided

  std::vector<std::vector<std::shared_ptr<Object>>> theFloor;   // tow dimention vector to record the layout of the floor
  std::vector<std::shared_ptr<Chamber>> theChambers;           // vector to store the information of the chambers
  std::vector<std::shared_ptr<Potion>> potionList;             // vector to store the information of the potions
  std::vector<std::shared_ptr<Treasure>> treasureList;         // vector to store the information of the treasures
  std::vector<std::shared_ptr<Enemy>> enemyList;               // vector to store the information of the enemy
  std::shared_ptr<Player> p;                                   // a pointer to the player
  std::shared_ptr<TextDisplay> td;                             // a pointer to the textdisplay
  std::shared_ptr<Stair> stair;                                // a pointer to the floor

  // the random generator
  Tile *randomTileGenerator();                                 // return a randomly generated tile which is not occupied
  void putPlayer(char type);
  void putEnemy();
  void putTreasure();
  void putPotion();
  void putStair();


  bool checkPotion(Tile *cur);                                 // returns true if there are potions surrounded the tile
  bool adjacent(Object *ob1, Object *ob2);                     // returns true if ob1 and ob2 are adjecent to each other

  void setTextDisplay(TextDisplay *td);                        // set TextDisplay to all of the object on the tile

 public:
  int chamber(int col, int row);   // return the chamber number (0, 1, 2, 3, 4) the specific object locate in 
  Floor(int level);
  ~Floor();

  void floorGenerator(std::string filename);                   // generate the floor based on the layout specified in the file filename
  void init(char type, std::string filename);                  
                                   // initalize the floor and spawn item (potion, treasure, enemy) on the floor

  bool moverForPlayer(std::string direction);
  void moverForEnemy();

  void usePotion(std::string direction);
  void buyPotion(std::string direction, std::string potion);

  // accessor: return any item on the floor
  Object *getItem(int col, int row);                             // return the Object at (col, row)
  Object *getItemInDirection(int col, int row, std::string direction);  // return the Object in a specific direction
  Player *getPlayer();
  int getLevel();
  TextDisplay *getDisplay();
  void statusNotify();                                            // notify the TextDisplay the state of the player

  void setPlayer(std::shared_ptr<Player> newone);

  void enemyAtk();
  void playerAtk(std::string direction);

  bool playerIsAlive();                                             // return true if the player has hp larger than 0

  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

std::ostream &operator<<(std::ostream &out, const Floor &f);

#endif
