#include "treasure.h"
#include "player.h"


Treasure::Treasure(int x, int y): Object{x, y} {
  symbol = 'G';
}


Treasure::~Treasure() {}


void Treasure::changeAvailability() { collectable = true; }


bool Treasure::canBeCollected() { return collectable; }


int Treasure::getValue() const { return value; }


void Treasure::sendGoldTo(Player &p) const {
  sendGold(p);
}


Normal::Normal(int x, int y): Treasure{x, y} {
  value = 1;
  name = "normal horde";
}


void Normal::sendGold(Player &p) const {
  collectable = true;
  p.getNormalGold();
}


Normal::~Normal() {}


Small::Small(int x, int y): Treasure{x, y} {
  value = 2;
  name = "small horde";
}


void Small::sendGold(Player &p) const {
  collectable = true;
  p.getSmallGold();
}


Small::~Small() {}


MerchantHrd::MerchantHrd(int x, int y): Treasure{x, y} {
  value = 4;
  name = "merchant horde";
}


void MerchantHrd::sendGold(Player &p) const {
  collectable = true;
  p.getMerchantGold();
}


MerchantHrd::~MerchantHrd() {}


DragonHrd::DragonHrd(int x, int y): Treasure{x, y} {
  collectable = false;
  value = 6;
  name = "dragon horde";
}


void DragonHrd::sendGold(Player &p) const {
  collectable = true;
  p.getDragonGold();
}

bool DragonHrd::isProtected() const { return protect; }

void DragonHrd::setProtected() { protect = true; }


DragonHrd::~DragonHrd() {}

