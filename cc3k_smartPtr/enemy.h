#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include <vector>


class Player;
class Treasure;
class DragonHrd;

class Enemy: public Character {
 protected:
  int calculateDamage(Player &p);
  bool hostile = true;
 public:
  Enemy(int x, int y);
  virtual void getAttack(Player &p);
  virtual void attack(Player &p);
  bool isHostile();
  ~Enemy();
};


class Vampire: public Enemy {
 public:
  Vampire(int x, int y);
  ~Vampire();
};



class Werewolf: public Enemy {
 public:
  Werewolf(int x, int y);
  void attack(Player &p) override;        // implement the special ability of Werewolf to become wolf, which increase the Atk
                                          // points by 10 points
  ~Werewolf();
};


class Troll: public Enemy {
 public:
  Troll(int x, int y);
  void getAttack(Player &p) override;      // implement the special ability of troll to regenerate by 5 points HP
  ~Troll();
};


class Globin: public Enemy {
 public:
  Globin(int x, int y);
  void attack(Player &p) override;      // implement the special ability of Globin to steal 1 gold from the player
  ~Globin();
};


class Merchant: public Enemy {
  std::vector <Merchant *> friends;
 public:
  Merchant(int x, int y);
  void getAttack(Player &p) override;
  void attachfriend(Merchant *m);
  void notifyfriend();
  void notify();
  ~Merchant();
};



class Phoenix: public Enemy {
 public:
  Phoenix(int x, int y);
  void getAttack(Player &p) override;  // implement the special ability of Phoenix to revive with probability 1/3
  ~Phoenix();
};


class Dragon: public Enemy {
  Treasure *hrd;
 public:
  Dragon(int x, int y, Treasure *hrd);
  Treasure* getHrd();
  void getAttack(Player &p) override;
  void getHostile();
  void setHrd(DragonHrd *dh);
  ~Dragon();
};

#endif
