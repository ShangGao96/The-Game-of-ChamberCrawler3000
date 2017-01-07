#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "character.h"
#include "treasure.h"
#include "textdisplay.h"
#include <string>
#include <sstream>
using namespace std;


Player::Player(int x, int y): Character{x,y} {
  symbol ='@';
}


Player::Player(const Player &other): Character{other} {}


float Player::numGold() const { return gold; }


void Player::setGold(int num) {
  gold = num;
}


void Player::setHP(int h) { curHP = h; }
void Player::setAtk(int a) { curAtk = a; }
void Player::setDef(int d) {curDef = d; }


bool Player::hasSpecial() const {
  return special != nullptr;
}


void Player::getAttack(Enemy &m) {
  int damage;
  if (special) {
    damage = (m.getAtk() * 100) / (100 + special->getDef());
    if (damage * (100 + special->getDef()) != (m.getAtk() * 100)) ++ damage;
  } else {
    damage = (m.getAtk() * 100) / (100 + curDef);
    if (damage * (100 + curDef) != (m.getAtk() * 100)) ++ damage;
  }
  ostringstream oss;
  oss << "Under ATTACK !! " << m.getSymbol() << " deals " << damage << " damages to PC. ";
  string s = oss.str();
  td->addAction(s);
  
  if (special) {
    special->curHP -= damage;
  }
  curHP -= damage;
  if (curHP <= 0) {
    live = false;
    curHP = 0;
    if (special) {
      special->curHP = 0;
    }
  }
}



void Player::attack(Enemy &m) {
  m.getAttack(*this);
}



Player *Player::createPlayer() {
  Player *newone;
  string name = getName();
  int x = getX();
  int y = getY();

  if (getName() == "human") {
    newone = new Human{x, y};
  } else if (getName() == "dwarf") {
    newone = new Dwarf{x, y};
  } else if (getName() == "elves") {
    newone = new Elves{x, y};
  } else if (getName() == "orc") {
    newone = new Orc{x, y};
  }
  newone->gold = numGold();
  newone->curHP = getHP();;
  newone->curAtk = getAtk();
  newone->curDef = getDef();
  return newone;
}



void Player::usePotion(Potion &p) {
  string s = p.getFunction();
  if (s == "RH") {
  
    increaseHP();
    if (special) special->increaseHP();
  
  } else if (s == "PH") {

    decreaseHP();
    if (special) special->decreaseHP();

  } else {
    if (special == nullptr) {
      special = createPlayer();
    }
    if (s == "BA") special->increaseAtk();
    if (s == "BD") special->increaseDef();
    if (s == "WA") special->decreaseAtk();
    if (s == "WD") special->decreaseDef(); 
  }
  ostringstream oss;
  oss << "PC uses the potion " << s << ". ";
  td->addAction(oss.str());
}


void Player::increaseHP() {
  curHP += 10;
  if (curHP > beginHP) curHP = beginHP;
}


void Player::increaseAtk() {
  curAtk += 5;
}


void Player::increaseDef() {
  curDef += 5;
}


void Player::decreaseHP() {
  curHP -= 10;
  if (curHP < 0) { curHP = 0; }
  
}


void Player::decreaseAtk() {
  curAtk -= 5;
  if (curAtk < 0) { curAtk = 0; }  
}


void Player::decreaseDef() {
  curDef -= 5;
  if (curDef < 0) { curDef = 0; }  
}


void Player::getGold(Treasure *t) {
  t->sendGoldTo(*this);  
}


void Player::getDropGold() {
  gold += 1;
  if (special) special->setGold(gold);
}


void Player::getNormalGold() {
  gold += 1;
  if (special) special->setGold(gold);
}


void Player::getSmallGold() {
  gold += 2;
  if (special) special->setGold(gold);
}


void Player::getMerchantGold() {
  gold += 4;
  if (special) special->setGold(gold);
}


void Player::getDragonGold() {
  gold += 6;
  if (special) special->setGold(gold);
}


Player::~Player() {
  if (special) delete special;
}



// *******  Human **********************

Human::Human(int x, int y): Player{x,y} {
  name = "human";
  beginHP = 140;
  beginAtk = 20;
  beginDef = 20;
  curHP = 140;
  curAtk = 20;
  curDef = 20;
}

Human::~Human() {}

// ********* Dwarf **********************

Dwarf::Dwarf(int x, int y): Player{x, y} {
  name = "dwarf";
  beginHP = 100;
  beginAtk = 20;
  beginDef = 30;
  curHP = 100;
  curAtk = 20;
  curDef = 30;
}

void Dwarf::getDropGold() {
  gold = gold + 1 * 2;
  if (special) special->setGold(gold);
}

void Dwarf::getNormalGold() {
  gold = gold + 1 * 2;
  if (special) special->setGold(gold);
}

void Dwarf::getSmallGold() {
  gold = gold + 2 * 2;
  if (special) special->setGold(gold);
}

void Dwarf::getMerchantGold() {
  gold = gold + 4 * 2;
  if (special) special->setGold(gold);
}

void Dwarf::getDragonGold() {
  gold = gold + 6 * 2;
  if (special) special->setGold(gold);
}

Dwarf::~Dwarf() {}

// ******* Elves ***********************

Elves::Elves(int x, int y): Player{x, y} {
  name = "elves";
  beginHP = 140;
  beginAtk = 30;
  beginDef = 10;
  curHP = 140;
  curAtk = 30;
  curDef = 10;
}


void Elves::decreaseHP() {
  curHP += 10;
  if (curHP > beginHP) curHP = beginHP;
 
}

void Elves::decreaseAtk() {
  curAtk += 5;
 
}

void Elves::decreaseDef() {
  curDef += 5;
}

Elves::~Elves() {}


// ******** Orc ***********************


Orc::Orc(int x, int y): Player{x, y} {
  name = "orc";
  beginHP = 180;
  beginAtk = 30;
  beginDef = 25;
  curHP = 180;
  curAtk = 30;
  curDef = 25;
}

void Orc::getDropGold() {
  gold = gold + 0.5;
  if (special) special->setGold(gold);
 
}

void Orc::getNormalGold() {
  gold = gold + 0.5;
  if (special) special->setGold(gold);
  
}

void Orc::getSmallGold() {
  gold = gold + 1;
  if (special) special->setGold(gold);
}

void Orc::getMerchantGold() {
  gold += 2;
  if (special) special->setGold(gold);
}

void Orc::getDragonGold() {
  gold += 3;
  if (special) special->setGold(gold);
}

Orc::~Orc() {}
