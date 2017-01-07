#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include <vector>

class Enemy;
class Potion;
class Treasure;


class Player: public Character {
 protected:
  float gold = 0;
 public:
  Player *special = nullptr;          // special player is created when the Player use potion BA, BD, WA, WD
  Player(int x, int y);
  Player(const Player &other);
  float numGold() const;              // return the number of gold Player currently holds
  void setGold(int num);
  void setHP(int h);
  void setAtk(int a);
  void setDef(int d);

  bool hasSpecial() const;

  // use potions
  void usePotion(Potion &p);
  Player *createPlayer();
  virtual void increaseHP();
  virtual void increaseAtk();
  virtual void increaseDef();
  virtual void decreaseHP();
  virtual void decreaseAtk();
  virtual void decreaseDef();

  // get treasure
  void getGold(Treasure *t);
  virtual void getDropGold();
  virtual void getNormalGold();
  virtual void getSmallGold();
  virtual void getMerchantGold();
  virtual void getDragonGold();

                    
  void getAttack(Enemy &m);
  void attack(Enemy &m);

  ~Player();
};



class Human final: public Player {
 public:
  Human(int x, int y);
  ~Human();
};


class Dwarf final: public Player {
 public:
  Dwarf(int x, int y);
  void getDropGold() override;
  void getNormalGold() override;
  void getSmallGold() override;
  void getMerchantGold() override;
  void getDragonGold() override;
  ~Dwarf();
};


class Elves final: public Player {
 public:
  Elves(int x, int y);
  void decreaseHP() override;
  void decreaseAtk() override;
  void decreaseDef() override;
  ~Elves();
};


class Orc final: public Player {
 public:
  Orc(int x, int y);
  void getDropGold() override;
  void getNormalGold() override;
  void getSmallGold() override;
  void getMerchantGold() override;
  void getDragonGold() override;
  ~Orc();
};


#endif

