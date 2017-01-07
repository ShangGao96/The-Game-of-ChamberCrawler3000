#include "character.h"
#include "stair.h"
#include "tile.h"
#include "passage.h"
#include "door.h"
#include "hwall.h"
#include "vwall.h"
#include "enemy.h"
#include "player.h"
#include "potion.h"
#include "treasure.h"
#include "chamber.h"
#include "space.h"
#include "object.h"
#include "floor.h"
#include "textdisplay.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <sstream>
using namespace std;

 
Floor::Floor(int level): level{level} {}


int Floor::getLevel() { return level; }


TextDisplay *Floor::getDisplay() { return td.get(); }


void Floor::floorGenerator(string filename) {

  for (int i = 0; i < 5; ++i) {                               // generate the five chambers
    shared_ptr<Chamber> chm = make_shared<Chamber>(Chamber{i});
    theChambers.emplace_back(chm);
  }


  ifstream structure;
  structure.exceptions(ios::failbit | ios::eofbit);

  try {
    structure.open(filename);
  }
  catch (ios::failure &) {
    cerr << "cannot open the file " << filename << endl;
    return;
  }
  ifstream defaultfloor("floor.txt");
  string s;
    for (int row = 0; row < 25; ++row) {                     // add all the item into the floor (tile, door, wall, passage)
      getline(defaultfloor, s);
      vector <shared_ptr<Object>> rItem;
      for (int col = 0; col < 79; ++col) {
        if (s.at(col) == '|') {
          auto wall = make_shared<Vwall>(Vwall{col, row});
          rItem.emplace_back(wall);
        } else if (s.at(col) == '-') {
          auto wall = make_shared<Hwall>(Hwall{col, row});
          rItem.emplace_back(wall);
        } else if (s.at(col) == '+') {
          int chamIndex = chamber(col, row);
          auto dr = make_shared<Door>(Door{col, row, chamIndex});
          rItem.emplace_back(dr);
        } else if (s.at(col) == '#') {
          auto psg = make_shared<Passage>(Passage{col, row});
          rItem.emplace_back(psg);
        } else if (s.at(col) == '.') {
          int chamIndex = chamber(col, row);
          auto t = make_shared<Tile>(Tile{col, row, chamIndex});
          rItem.emplace_back(t);
          theChambers[chamIndex]->addTile(t.get());
        } else if (s.at(col) == ' ') {
          auto sp = make_shared<Space>(Space{col, row});
          rItem.emplace_back(sp);
        }
      }
    theFloor.emplace_back(rItem);
  }

  // add neighbor to all the tiles
  for (int i = 0; i < 5; ++i) {
    auto tmp = theChambers.at(i);
    for(int j = 0; j < tmp->getSize(); ++j) {
      Tile *ti = tmp->getTile(j);
      tmp->addNeighbor(ti);
    }
  }

  // the case where a specific layout of the floor is provided
  if (filename != "floor.txt") {
    fileProvided = true;

    int startLine = 25 * (level-1);
    for (int line = 1; line <= startLine; ++line) {
      getline(structure, s);  
    }

    for (int row = 0; row < 25; ++row) {
      getline(structure, s);
      for (int col = 0; col < 79; ++col) {
        Object *cur = getItem(col, row);
        if (Tile *curTile = dynamic_cast<Tile*>(cur)) {

          if (s.at(col) == '0') {  // 0-RH
            auto newpotion = make_shared<Potion>(Potion{col, row, "RH"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '1') {  // 1-BA
            auto newpotion = make_shared<Potion>(Potion{col, row, "BA"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '2') {  // 2-BD
            auto newpotion = make_shared<Potion>(Potion{col, row, "BD"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '3') {   // 3-PH
            auto newpotion = make_shared<Potion>(Potion{col, row, "PH"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '4') {    // 4-WA
            auto newpotion = make_shared<Potion>(Potion{col, row, "WA"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '5') {     // 5-WD
            auto newpotion = make_shared<Potion>(Potion{col, row, "WD"});
            curTile->putObject(newpotion.get());
            potionList.emplace_back(newpotion);
          } else if (s.at(col) == '6') {     // 6-Normal Gold
            auto newtreasure = make_shared<Normal>(Normal{col, row});
            curTile->putObject(newtreasure.get());
            treasureList.emplace_back(newtreasure);
          } else if (s.at(col) == '7') {     // 7-small gold
            auto newtreasure = make_shared<Small>(Small{col, row});
            curTile->putObject(newtreasure.get());
            treasureList.emplace_back(newtreasure);
          } else if (s.at(col) == '8') {     // 8-Merchant Horde
            auto newtreasure = make_shared<MerchantHrd>(MerchantHrd{col, row});
            curTile->putObject(newtreasure.get());
            treasureList.emplace_back(newtreasure);
          } else if (s.at(col) == '9') {      // 9-Dragon Horde
            auto newtreasure = make_shared<DragonHrd>(DragonHrd{col, row});
            curTile->putObject(newtreasure.get());
            treasureList.emplace_back(newtreasure);
          } else if (s.at(col) == 'V') {
            auto newenemy = make_shared<Vampire>(Vampire{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'W') {
            auto newenemy = make_shared<Werewolf>(Werewolf{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'N') {
            auto newenemy = make_shared<Globin>(Globin{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'M') {
            auto newenemy = make_shared<Merchant>(Merchant{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'D') {
            auto newenemy = make_shared<Dragon>(Dragon{col, row, nullptr});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'X') {
            auto newenemy = make_shared<Phoenix>(Phoenix{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == 'T') {
            auto newenemy = make_shared<Troll>(Troll{col, row});
            curTile->putObject(newenemy.get());
            enemyList.emplace_back(newenemy);
          } else if (s.at(col) == '\\') {
            auto newstair = make_shared<Stair>(Stair{col, row, chamber(col, row)});
            curTile->putObject(newstair.get());
            stair = newstair;
          }
        }
      }
    }


    for (int row = 0; row < theFloor.size(); ++row) {
      for (int col = 0; col < theFloor.at(row).size(); ++col) {
        if (auto t = dynamic_pointer_cast<Tile>(theFloor[row][col])) {
          if (DragonHrd *dh = dynamic_cast<DragonHrd*>(t->item())) {
            bool addSuccess = false;
            for (int r = row - 1; r <= row + 1; ++r) {
              for (int c = col - 1; c <= col + 1; ++c) {
                if (auto t1 = dynamic_pointer_cast<Tile>(theFloor[r][c])) {
                  if (Dragon *dra = dynamic_cast<Dragon*>(t1->item())) {
                    if (dra->getHrd() == nullptr) {
                      dra->setHrd(dh);
                      addSuccess = true;
                      break;
                    }
                  }
                }
                if (addSuccess) break;
              }
            }
          }
        }
      }
    }

    // add friends to every merchant
    for (int i = 0; i < enemyList.size(); ++i) {
      if (auto m = dynamic_pointer_cast<Merchant>(enemyList.at(i))) {
        for (int j = 0; j < enemyList.size(); ++j) {
          if (auto fri = dynamic_pointer_cast<Merchant>(enemyList.at(j))) {
            if (i != j) {
              m->attachfriend(fri.get());
            }
          }
        }
      }
    }
  }
}



int Floor::chamber(int col, int row) { 
  if (row > 2 && row < 7 && col > 2 && col < 29) return 0;
  if ((row >= 3 && row <= 4 && col >= 39 && col <= 61) ||
                   (row == 5 && col >= 39 && col <= 69) ||
                   (row == 6 && col >= 39 && col <= 72) ||
                   (row >= 7 && row <= 12 && col >= 61 && col <= 75)) return 1;
  if (row > 9 && row < 13 && col > 37 && col < 50) return 2;
  if (row > 14 && row < 22 && col > 3 && col < 25) return 3;
  if ((row >= 16 && row <= 18 && col >= 65 && col <= 75) ||
      (row >= 19 && row <= 21 && col >= 37 && col <= 75)) return 4;
  return -1;   // -1 means that the specific position is not in any chambers
}



Tile *Floor::randomTileGenerator() {
  auto randomChamber = theChambers.at(rand() % theChambers.size());

  Tile *randomTile = randomChamber->getTile(rand() % randomChamber->getSize());
  while (randomTile->isOccupied()) {
    randomChamber = theChambers.at(rand() % theChambers.size());
    randomTile = randomChamber->getTile(rand() % randomChamber->getSize());
  }
  return randomTile;
}



void Floor::putPlayer(char type) {
  Tile *position = randomTileGenerator();

  int row = position->getY();
  int col = position->getX();
  if (p == nullptr) {
    if (type == 'h') {
      p = make_shared<Human>(Human{col, row});
    } else if (type == 'e') {
      p = make_shared<Elves>(Elves{col, row});
    } else if (type == 'd') {
      p = make_shared<Dwarf>(Dwarf{col, row});
    } else if (type == 'o') {
      p = make_shared<Orc>(Orc{col, row});
    }
    position->putObject(p.get());
  } else {
    p->setX(col);
    p->setY(row);
    position->putObject(p.get());
  }
}



void Floor::putEnemy() {
  Tile *position = randomTileGenerator();
  int row = position->getY();
  int col = position->getX();
  
  shared_ptr<Enemy> em;

  int sizeofEnemyList = enemyList.size();
  for (int i = 0; i < numEnemy - sizeofEnemyList; ++i) {
    int possibility = rand() % 18;
    if (possibility >= 0 && possibility < 4) {
      em = make_shared<Werewolf>(Werewolf{col, row});
    } else if (possibility >= 4 && possibility < 7) {
      em = make_shared<Vampire>(Vampire{col, row});
    } else if (possibility >= 7 && possibility < 12) {
      em = make_shared<Globin>(Globin{col, row});
    } else if (possibility >= 12 && possibility < 14) {
      em = make_shared<Phoenix>(Phoenix{col, row});
    } else if (possibility >= 14 && possibility < 16) {
      em = make_shared<Troll>(Troll{col, row});
    } else if (possibility >= 16 && possibility < 18) {
      em = make_shared<Merchant>(Merchant{col, row});
    }
    position->putObject(em.get());
    enemyList.emplace_back(em);

    position = randomTileGenerator();
    row = position->getY();
    col = position->getX();
  }

  // add the merchant friends to merchant
  for (int i = 0; i < enemyList.size(); ++i) {
    if (auto m = dynamic_pointer_cast<Merchant>(enemyList.at(i))) {
      for (int j = 0; j < enemyList.size(); ++j) {
        if (auto fri = dynamic_pointer_cast<Merchant>(enemyList.at(j))) {
         if (i != j) {
           m->attachfriend(fri.get());
         }
        }
      }
    }
  }

  // sort the enemy list by line by line fation
  std::vector<std::shared_ptr<Enemy>> newenemyList;
  for (int row = 0; row < theFloor.size(); ++row) {
    for (int col = 0; col < theFloor[row].size(); ++col) {
      for (int k = 0; k < enemyList.size(); ++k) {
        if (enemyList.at(k)->getX() == col && enemyList.at(k)->getY() == row) {
          newenemyList.emplace_back(enemyList.at(k));
        }
      }
    }
  }
  enemyList = newenemyList;
}



void Floor::putStair() {
  Tile *position = randomTileGenerator();
  int row = position->getY();
  int col = position->getX();
  
  int playerCham = chamber(p->getX(), p->getY());
  int chamIndex = chamber(col, row);
  while(chamIndex == playerCham) position = randomTileGenerator();  
                                                   // to ensure that the player and stair are not in the same chamber
  auto st = make_shared<Stair>(Stair{col, row, chamIndex});
  position->putObject(st.get());
  stair = st;
}



void Floor::putPotion() {
  Tile *position = randomTileGenerator();
  int row = position->getY();
  int col = position->getX();

  shared_ptr<Potion> po;

  for (int i = 0; i < 10; ++i) {
    int possibility = rand() % 6;
    if (possibility == 0) {
      po = make_shared<Potion>(Potion{col, row, "RH"});      
    } else if (possibility == 1) {
      po = make_shared<Potion>(Potion{col, row, "BA"});
    } else if (possibility == 2) {
      po = make_shared<Potion>(Potion{col, row, "BD"});
    } else if (possibility == 3) {
      po = make_shared<Potion>(Potion{col, row, "PH"});
    } else if (possibility == 4) {
      po = make_shared<Potion>(Potion{col, row, "WA"});
    } else if (possibility == 5) {
      po = make_shared<Potion>(Potion{col, row, "WD"});
    }

    position->putObject(po.get());
    potionList.emplace_back(po);

    position = randomTileGenerator();
    row = position->getY();
    col = position->getX();
  }
}



void Floor::putTreasure() {
  Tile *position = randomTileGenerator();
  int row = position->getY();
  int col = position->getX();

  shared_ptr<Treasure> t;

  for (int i = 0; i < 10; ++i) {
    int possibility = rand() % 8;
    if (possibility >= 0 && possibility < 5) {        // normal horde
      t = make_shared<Normal>(Normal{col, row});
    } else if (possibility >= 5 && possibility < 6) {  // dragon horde
      t = make_shared<DragonHrd>(DragonHrd{col, row});

      unsigned int seed = position->neighborSize();
      int randomNum = rand() % seed;                  // generate a dragon to protect the dragon horde

      Tile *putDragon = position->getNeighbor(randomNum);

      while (putDragon->isOccupied()) {
        randomNum = rand() % seed;
        putDragon = position->getNeighbor(randomNum);
      }

      auto dragon = make_shared<Dragon>(Dragon{putDragon->getX(), putDragon->getY(), t.get()});
      //t->setProtected();

      putDragon->putObject(dragon.get());
      enemyList.emplace_back(dragon);
            
    } else if (possibility >= 6 && possibility < 8) {   // small horde
      t = make_shared<Small>(Small{col, row});
    }

    position->putObject(t.get());
    treasureList.emplace_back(t);

    position = randomTileGenerator();
    row = position->getY();
    col = position->getX();
  }
}



Object *Floor::getItem(int col, int row) {
  return theFloor[row][col].get();
}



Player *Floor::getPlayer() { return p.get(); }



void Floor::setPlayer(shared_ptr<Player> newPlayer) {
  p = newPlayer;
}



Floor::~Floor() {}


void Floor::setTextDisplay(TextDisplay *td) {
  for (int row = 0; row < static_cast<int>(theFloor.size()); ++row) {
    for (int col = 0; col < static_cast<int>(theFloor.at(row).size()); ++col) {

      theFloor[row][col]->setTextDisplay(td);
      if (auto tile = dynamic_pointer_cast<Tile>(theFloor[row][col])) {

        if (tile->isOccupied()) {
          tile->item()->setTextDisplay(td);
        }
      }
    }
  }
}



void Floor::init(char type, string filename) {
  if (filename == "floor.txt") {
    putPlayer(type);
  } else {
    ifstream structure(filename);
    string s;
    int startLine = 25 * (level-1);
    for (int line = 1; line <= startLine; ++line) {
      getline(structure, s);
    }
    for (int row = 0; row < 25; ++row) {
      getline(structure, s);
      for (int col = 0; col < 79; ++col) {
        auto cur = getItem(col, row);
        if (Tile* curTile = dynamic_cast<Tile*>(cur)) {
          if (s.at(col) == '@') {
            auto tile = dynamic_cast<Tile*>(getItem(col, row));
            if (!p) {
              if (type == 'h') {
                p = make_shared<Human>(Human{col, row});
              } else if (type == 'e') {
                p = make_shared<Elves>(Elves{col, row});
              } else if (type == 'd') {
                p = make_shared<Dwarf>(Dwarf{col, row});
              } else if (type == 'o') {
                p = make_shared<Orc>(Orc{col, row});
              }
              tile->putObject(p.get());
            } else {
              p->setX(col);
              p->setY(row);
              tile->putObject(p.get());
            }
          }
        }
      }
    }
  }

  string message;
  if (level == 1) {
    message = "Welcome to the Game of ChamberCrawler3000. ";
  } else {
    ostringstream oss;
    oss << "Welcome to the " << level << " floor. Now, you can begin. ";
    message = oss.str();
  }
  td = make_shared<TextDisplay>(TextDisplay{p->getName(), p->getHP(), p->getAtk(),
         p->getDef(), p->numGold(), level, message});
                                                  // create a TextDisplay to observe the floor
  td->setFloor(this);
  if (!fileProvided) {
    putStair();
    putPotion();
    putTreasure();
    putEnemy();
  }
  setTextDisplay(td.get());
  td->init();
}



void Floor::moverForEnemy() {
  int enemyNum = enemyList.size();
  for (int i = 0; i < enemyNum; ++i) {

    auto tmp = enemyList.at(i).get();

    if (tmp->getName() == "dragon") continue;         // dragon is stationary

    int row = tmp->getY();
    int col = tmp->getX();
    Tile *curposition = dynamic_cast<Tile*>(getItem(col, row));

    int neighborNum = curposition->neighborSize();

    bool allOccupied;

    for (int j = 0; j < neighborNum; ++j) {
      if (curposition->getNeighbor(j)->isOccupied()) {
         allOccupied = true;
      } else {
         allOccupied = false;
         break;
      }
    }

    if (allOccupied) continue;                  // all the neighbor is occupied, so this enemy canot move

    int possibility = rand() % neighborNum;
    Tile *nextposition = curposition->getNeighbor(possibility);

    while (nextposition->isOccupied()) {
      possibility = rand() % neighborNum;
      nextposition = curposition->getNeighbor(possibility);
    }                                           // find the next position to move on
   
    int newrow = nextposition->getY();
    int newcol = nextposition->getX();
    
    tmp->setX(newcol);
    tmp->setY(newrow); 
    nextposition->putObject(tmp);
    curposition->emptied();


    td->notify(nextposition);
    td->notify(curposition);
  }
  enemyAtk();
}



Object *Floor::getItemInDirection(int col, int row, string direction) {
  Object *destination = nullptr;
  if (direction == "no") destination = getItem(col, row-1);
  if (direction == "ne") destination = getItem(col+1, row-1);
  if (direction == "ea") destination = getItem(col+1, row);
  if (direction == "se") destination = getItem(col+1, row+1);
  if (direction == "so") destination = getItem(col, row+1);
  if (direction == "sw") destination = getItem(col-1, row+1);
  if (direction == "we") destination = getItem(col-1, row);
  if (direction == "nw") destination = getItem(col-1, row-1);
  return destination;
}



bool Floor::moverForPlayer(string direction) {
  int curX = p->getX();
  int curY = p->getY();
  Object *curposition = getItem(curX, curY);
  Object *nextposition = getItemInDirection(curX, curY, direction);

  if (nextposition->getSymbol() == '|' || nextposition->getSymbol() == '-') {
    td->addAction("You cannot walk on the wall. ");
  } else if (nextposition->getSymbol() == '\\') {
    ostringstream oss;
    oss << "PC moves " << direction << ", and onto the stair. Now, you can go to the next floor. ";
    td->addAction(oss.str());
    return true;
  } else if (nextposition->getSymbol() == ' ') {
    td->addAction("You cannot walk on the white space. ");
  } else if (Tile *next = dynamic_cast<Tile*>(nextposition)) {
    if (next->isOccupied()) {
      Object *it = next->item();

      if (it->getSymbol() == 'G') {          // the next postion is treasure
        Treasure *treasure = dynamic_cast<Treasure*>(it);
          if (treasure->canBeCollected()) {
            ostringstream oss1;
            oss1 << "Get a " << treasure->getName() << ", ";
            td->addAction(oss1.str());
            p->getGold(treasure);
            next->emptied();
            p->setX(next->getX());
            p->setY(next->getY());
            next->putObject(p.get());
            td->notify(next);
            if (Tile *tmp = dynamic_cast<Tile*>(curposition)) {
              tmp->emptied();
              td->notify(tmp);
            }
            if (Door *tmp = dynamic_cast<Door*>(curposition)) {
              tmp->emptied();
              td->notify(tmp);
            }
            ostringstream oss;
            oss << "PC moves " << direction << ". ";
            td->addAction(oss.str());
          } else if (DragonHrd *dragonhrd = dynamic_cast<DragonHrd*>(it)) {
            if (!dragonhrd->canBeCollected()){
              td->addAction("You cannot get dragon horde. You must kill dragon first. ");
          }
        }
      } else {
        td->addAction("You cannot move on an occupied tile. ");
      }
    } else {                     // next positon is tile, door, passage
      p->setX(next->getX());
      p->setY(next->getY());
      next->putObject(p.get());
      td->notify(next);
      if (Tile *tmp = dynamic_cast<Tile*>(curposition)) {
        tmp->emptied();
        td->notify(tmp);
      }
      if (Door *tmp = dynamic_cast<Door*>(curposition)) {
        tmp->emptied();
        td->notify(tmp);
      }
      ostringstream oss;
      oss << "PC moves " << direction << ". ";
      td->addAction(oss.str());
    }
  } else if (Door *next = dynamic_cast<Door*>(nextposition)) {
    p->setX(next->getX());
    p->setY(next->getY());
    next->putObject(p.get());
    td->notify(next);
    if (Tile *tmp = dynamic_cast<Tile*>(curposition)) {
      tmp->emptied();
      td->notify(tmp);
    }
    if (Passage *tmp = dynamic_cast<Passage*>(curposition)) {
      tmp->emptied();
      td->notify(tmp);
    }
    ostringstream oss;
    oss << "PC moves " << direction << " and onto the door. ";
    td->addAction(oss.str());
  } else if (Passage *next = dynamic_cast<Passage*>(nextposition)) {
    p->setX(next->getX());
    p->setY(next->getY());
    next->putObject(p.get());
    td->notify(next);
    if (Door *tmp = dynamic_cast<Door*>(curposition)) {
      tmp->emptied();
      td->notify(tmp);
    }
    if (Passage *tmp = dynamic_cast<Passage*>(curposition)) {
      tmp->emptied();
      td->notify(tmp);
    }
    ostringstream oss;
    oss << "PC moves " << direction << " and onto the passage to other chamber. ";
    td->addAction(oss.str());
  }
  moverForEnemy();
  if (Tile *next = dynamic_cast<Tile*>(nextposition)) {
    if (checkPotion(next)) {
      td->addAction("PC sees an unknown potion. ");
    }
  }
  return false;
}



bool Floor::checkPotion(Tile *cur) {
  for (int i = 0; i < cur->neighborSize(); ++i) {
    if (cur->getNeighbor(i)->getSymbol() == 'P') {
      return true;
    }
  }
  return false;
}



void Floor::usePotion(std::string direction) {
  int curX = p->getX();
  int curY = p->getY();

  Object *cur = getItem(curX, curY);
  
  Object *next = getItemInDirection(curX, curY, direction);
  Tile *nextposition = static_cast<Tile*>(next);
  
  if (Potion *po = dynamic_cast<Potion *>(nextposition->item())) {
    p->usePotion(*po);
    p->setX(nextposition->getX());
    p->setY(nextposition->getY());
    nextposition->putObject(p.get());
    td->notify(nextposition);
    if (Tile *curposition = dynamic_cast<Tile*>(cur)) {
      curposition->emptied();
      td->notify(curposition);
    }
    if (Door *curposition = dynamic_cast<Door*>(cur)) {
      curposition->emptied();
      td->notify(curposition);
    }
  } else {
    td->addAction("The item is not a potion. ");
  }
  moverForEnemy();
}



void Floor::buyPotion(string direction, string potion) {
  // money information:
  //  "RH": 5 gold
  //  "BA": 4 gold
  //  "BD": 3 gold

  float goldamount = p->numGold();

  int curX = p->getX();
  int curY = p->getY();

  Object *cur = getItem(curX, curY);
  
  Object *next = getItemInDirection(curX, curY, direction);
  Tile *nextposition = static_cast<Tile*>(next);
  if (nextposition->item()->getName() != "merchant") {
    td->addAction("You can only buy potions from merchant. ");
    return;
  }

  if (potion == "RH") {
    if (goldamount >= 5) {
      Potion *po = new Potion{0, 0, "RH"};
      p->usePotion(*po);
      p->setGold(goldamount - 5);
      if (p->hasSpecial()) {
        p->special->setGold(goldamount - 5);
      }
      delete po;
      td->addAction("You buy one RH. ");
    } else {
      td->addAction("Sorry, you do not have enough gold. ");
    }
  } else if (potion == "BA") {
    if (goldamount >= 4) {
      Potion *po = new Potion{0, 0, "BA"};
      p->usePotion(*po);
      p->setGold(goldamount - 4);
      if (p->hasSpecial()) {
        p->special->setGold(goldamount - 4);
      }
      delete po;
      td->addAction("You buy one BA, which is only functional in this floor. ");
    } else {
      td->addAction("Sorry, you do not have enough gold. ");
    }
  } else if (potion == "BD") {
    if (goldamount >= 3) {
      Potion *po = new Potion{0, 0, "BD"};
      p->usePotion(*po);
      p->setGold(goldamount - 3);
      if (p->hasSpecial()) {
        p->special->setGold(goldamount - 3);
      }
      delete po;
      td->addAction("You buy one BD, which is only functional in this floor. ");
    } else {
      td->addAction("Sorry, you do not have enough gold. ");
    }
  }
}



int abs(int x, int y) {
  if ((x - y) > 0) return x -y;
  return y - x;
}


bool Floor::adjacent(Object *ob1, Object *ob2) {
  int ob1X = ob1->getX();
  int ob1Y = ob1->getY();
  int ob2X = ob2->getX();
  int ob2Y = ob2->getY();
  if (abs(ob1X, ob2X) <= 1 && abs(ob1Y, ob2Y) <= 1) return true;
  return false;
}

void Floor::enemyAtk() {
  for (int i = 0; i < enemyList.size(); ++i) {
    auto em = enemyList.at(i).get();

    if (em->getName() == "dragon") {
      auto protector = dynamic_cast<Dragon*>(em);
      DragonHrd *hrd = dynamic_cast<DragonHrd *>(protector->getHrd());
      if (adjacent(p.get(), hrd)) {
        protector->getHostile();
        em->attack(*p.get());
      }
    } else {
      if (adjacent(p.get(), em) && em->isHostile()) {
        em->attack(*p.get());
      }
    }
  }
}



void Floor::playerAtk(string direction) {
  int curX = p->getX();
  int curY = p->getY();

  Object *cur = getItem(curX, curY);
  Object *next = getItemInDirection(curX, curY, direction);
  Tile *nextposition = dynamic_cast<Tile*>(next);

  if (Enemy *em = dynamic_cast<Enemy*>(nextposition->item())) {
    p->attack(*em);
    if (!em->isLive()) {
      nextposition->emptied();
      td->notify(nextposition);
      for (int i = 0; i < enemyList.size(); ++i) {
        auto tmp = enemyList.at(i).get();
        if (tmp->getX() == em->getX() && tmp->getY() == em->getY()) {
          --numEnemy;
          enemyList.erase(enemyList.begin() + i);
        }
      }
    }
    moverForEnemy();
  } else {
    td->addAction("There is no enemy in the given direction. ");
  }
}


void Floor::statusNotify() {
  if (p->hasSpecial()) {
    td->playernotify(p->special);
  } else {
    td->playernotify(p.get());
  }
}


bool Floor::playerIsAlive() { return p->isLive(); }



ostream &operator<<(ostream &out, const Floor &f) {
  out << *(f.td);
  return out;
}
