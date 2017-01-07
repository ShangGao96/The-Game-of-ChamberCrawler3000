#include "enemy.h"
#include "player.h"
#include "treasure.h"
#include "textdisplay.h"

#include <sstream>
using namespace std;


Enemy::Enemy(int x, int y): Character{x, y} {}


bool Enemy::isHostile() { return hostile; }


int Enemy::calculateDamage(Player &p) {
  int damage;
  if (p.hasSpecial()) {
    damage = (p.special->getAtk() * 100) / (100 + curDef);
    if (damage * (100 + curDef) != (p.special->getAtk() * 100)) ++damage;
  } else {
    damage = (p.getAtk() * 100) / (100 + curDef);
    if (damage * (100 + curDef) != (p.getAtk() * 100)) ++ damage;
  }
  return damage;
}


void Enemy::getAttack(Player &p) {
  int damage = calculateDamage(p);
  curHP -= damage;
  if (curHP <= 0) curHP = 0;

  ostringstream ss;
  ss << p.getName() << " deals " << damage << " damages to " << getSymbol() << " and " << getSymbol() << " has " << getHP() << " left. ";
  string s = ss.str();
  td->addAction(s);
  if (curHP <= 0) {
    p.getDropGold();
    live = false;
    curHP = 0;
    ostringstream oss;
    oss << getSymbol() << " is dead. And PC gets 1 gold reward. ";
    td->addAction(oss.str());
  }
};

void Enemy::attack(Player &p) {
  int attack = rand() % 2;
  if (attack == 1) {
    p.getAttack(*this);
  } else {
    td->addAction("PC is got attacked, but luckily missed. ");
  }
}

Enemy::~Enemy() {}


Vampire::Vampire(int x, int y): Enemy{x, y} {
  symbol = 'V';
  name = "vampire";
  beginHP = 50;
  beginAtk = 25;
  beginDef = 25;
  curHP = 50;
  curAtk = 25;
  curDef = 25;
}


Vampire::~Vampire() {}

Werewolf::Werewolf(int x, int y): Enemy{x, y} {
  symbol = 'W';
  name = "werewolf";
  beginHP = 120;
  beginAtk = 30;
  beginDef = 5;
  curHP = 120;
  curAtk = 30;
  curDef = 5;
}

void Werewolf::attack(Player &p) {
  int attack = rand() % 2;
  if (attack == 1) {
    int becomeWolf = rand() % 3;   // if the werewolf become wolf, its attak will increase by 10 points
                                   // the probability of becoming wolf is 1/3
    if (becomeWolf == 0) {
      curAtk = 35;
      td->addAction("Werewolf becomes wolf and its Atk points increase to 40. ");
    }
    p.getAttack(*this);
    curAtk = 30;
  } else {
    td->addAction("PC is got attacked, but luckily missed. ");
  }

}


Werewolf::~Werewolf() {}


Troll::Troll(int x, int y): Enemy{x, y} {
  symbol = 'T';
  name = "troll";
  beginHP = 120;
  beginAtk = 25;
  beginDef = 15;
  curHP = 120;
  curAtk = 25;
  curDef = 15;
}

void Troll::getAttack(Player &p) {
  int damage = calculateDamage(p);
  curHP = curHP - damage + 5;
  if (curHP <= 0) curHP = 0;
  td->addAction("Troll regenerate its health by 5 HP. ");             // the health regeneration for trolls

  ostringstream ss;
  ss << p.getName() << " deals " << damage << " damages to " << getSymbol() << " and " << getSymbol() << " has " << getHP() << " left. ";
  string s = ss.str();
  td->addAction(s);

  if (curHP <= 0) {
    p.getDropGold();
    live = false;
    curHP = 0;

    td->addAction("T is dead. And PC gets 1 gold reward. ");
  }
}


Troll::~Troll() {}


Globin::Globin(int x, int y): Enemy{x, y} {
  symbol = 'N';
  name = "goblin";
  beginHP = 70;
  beginAtk = 5;
  beginDef = 10;
  curHP = 70;
  curAtk = 5;
  curDef = 10;
}

void Globin::attack(Player &p) {
  int attack = rand() % 2;
  if (attack == 1) {
    p.getAttack(*this);
    if (p.numGold() > 0) {
      float steal = p.numGold() - 1;   // globin steal one gold
      if (steal < 0) steal = 0;
      td->addAction("Globin steal 1 gold from you. ");
      p.setGold(steal);
    }
  } else {
    td->addAction("PC is got attacked, but luckily missed. ");
  }
}

Globin::~Globin() {}

// ****************************************************
Merchant::Merchant(int x, int y): Enemy{x, y} {
  hostile = false;
  symbol = 'M';
  name = "merchant";
  beginHP = 30;
  beginAtk = 70;
  beginDef = 5;
  curHP = 30;
  curAtk = 70;
  curDef = 5;
}

void Merchant::getAttack(Player &p) {
  int damage = calculateDamage(p);
  curHP -= damage;
  if (curHP <= 0) curHP = 0;

  if (!hostile) {
    hostile = true;
    notifyfriend();
  }
  hostile = true;
  ostringstream ss;
  ss << p.getName() << " deals " << damage << " damages to " << getSymbol() << " and " << getSymbol() << " has " << getHP() << " left. ";
  string s = ss.str();
  td->addAction(s);

  if (curHP <= 0) {
    p.getMerchantGold();
    td->addAction("M is dead. And PC gets one Merchant Horde. ");
    live = false;
    curHP = 0;
  }
}


void Merchant::attachfriend(Merchant *m) {
  friends.emplace_back(m);
}

void Merchant::notifyfriend() {
  for (auto &ob: friends) ob->notify();
  td->addAction("All merchants are hostile now. ");
}

void Merchant::notify() {
  hostile = true;
}

Merchant::~Merchant() {
  friends.clear();
}

// *************************************************

Dragon::Dragon(int x, int y, Treasure *hrd): Enemy{x, y}, hrd{hrd} {
  hostile = false;
  symbol = 'D';
  name = "dragon";
  beginHP = 150;
  beginAtk = 20;
  beginDef = 20;
  curHP = 150;
  curAtk = 20;
  curDef = 20;
}

void Dragon::getAttack(Player &p) {
  int damage = calculateDamage(p);
  curHP -= damage;
  if (curHP <= 0) curHP = 0;

  ostringstream ss;
  ss << p.getName() << " deals " << damage << " damages to " << getSymbol() << " and " << getSymbol() << " has " << getHP() << " left. ";
  string s = ss.str();
  td->addAction(s);

  if (curHP <= 0) {
    td->addAction("The dragon is dead. Now, you can collect the dragon horde. ");
    hrd->changeAvailability();
    live = false;
    curHP = 0;
  }
}

void Dragon::getHostile() {
  hostile = true;
}


void Dragon::setHrd(DragonHrd *dh) {
  hrd = dh;
}


Treasure *Dragon::getHrd() {
  return hrd;
}

Dragon::~Dragon() {}

Phoenix::Phoenix(int x, int y): Enemy{x, y} {
  symbol = 'X';
  name = "Phoenix";
  beginHP = 50;
  beginAtk = 35;
  beginDef = 20;
  curHP = 50;
  curAtk = 35;
  curDef = 20;
}

void Phoenix::getAttack(Player &p) {
  int damage = calculateDamage(p);
  curHP -= damage;
  if (curHP <= 0) curHP = 0;

  ostringstream ss;
  ss << p.getName() << " deals " << damage << " damages to " << getSymbol() << " and " << getSymbol() << " has " << getHP() << " left. ";
  string s = ss.str();
  td->addAction(s);

  if (curHP <= 0) {
    int revive = rand() % 3;           // the Phoenix has 1/3 chance to revive if it is dead
    if (revive == 0) {                 // the Phoenix is revive
      td->addAction("Phoenix revives. ");
      curHP = beginHP;
    } else {
      p.getDropGold();
      live = false;
      curHP = 0;
      ostringstream oss;
      oss << getSymbol() << " is dead. And PC got 1 gold reward. ";
      td->addAction(oss.str());
    }
  }
}

Phoenix::~Phoenix() {}
