#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "object.h"

class Player;

class Treasure: public Object {
 protected:
  int value;
  mutable bool collectable = true;
  virtual void sendGold(Player &p) const = 0;
 public:
  Treasure(int x, int y);
  int getValue() const;
  void changeAvailability();
  bool canBeCollected();
  void sendGoldTo(Player &p) const;
  ~Treasure();
};


class Normal: public Treasure {
 public:
  Normal(int x, int y);
  void sendGold(Player &p) const override;
  ~Normal();
};


class Small: public Treasure {
 public:
  Small(int x, int y);
  void sendGold(Player &p) const override;
  ~Small();
};



class MerchantHrd: public Treasure {
 public:
  MerchantHrd(int x, int y);
  void sendGold(Player &p) const override;
  ~MerchantHrd();
};


class DragonHrd: public Treasure {
  mutable bool protect = false;
 public:
  bool isProtected() const;
  DragonHrd(int x, int y);
  void setProtected();
  void sendGold(Player &p) const override;
  ~DragonHrd();
};


#endif
