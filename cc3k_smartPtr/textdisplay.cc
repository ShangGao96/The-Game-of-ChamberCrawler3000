#include "textdisplay.h"
#include "floor.h"
#include "player.h"
#include "object.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


TextDisplay::TextDisplay(std::string race, int hp, int atk, int def, float gold, int level, std::string action):
   race{race}, hp{hp}, atk{atk}, def{def}, gold{gold}, level{level}, action{action} {}


void TextDisplay::init() {
	level = thefloor->getLevel();
	theDisplay.clear();
	for (int row = 0 ; row < 25; ++row) {
		vector<char> r;
		for (int col = 0; col < 79; ++col) {
			r.emplace_back(thefloor->getItem(col, row)->getSymbol());
		}
		theDisplay.emplace_back(r);
	}
}


void TextDisplay::notify(Object *ob) {
	int col = ob->getX();
	int row = ob->getY();
	theDisplay[row][col] = ob->getSymbol();
}



void TextDisplay::playernotify(Player *p) {
	hp = p->getHP();
	atk = p->getAtk();
	def = p->getDef();
	gold = p->numGold();
}


void TextDisplay::addAction(string act) {
	action = action + act;
}


void TextDisplay::setFloor(Floor *f) {
	thefloor = f;
}


 TextDisplay::~TextDisplay() {
 	theDisplay.clear();
 }


 void TextDisplay::clearAction() {
 	action = "";
 }


 std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
 	for (int row = 0 ; row < td.theDisplay.size(); ++row) {
		for (int col = 0; col < td.theDisplay.at(row).size(); ++col) {
			out << td.theDisplay[row][col];
		}
		out << endl;
	}
	out << "Race: " << td.race << " Gold: " << td.gold << setw(45) << "Floor " << td.level << endl
	<< "HP " << td.hp << endl
	<< "Atk: " << td.atk << endl
	<< "Def: " << td.def << endl
	<< "Action: " << td.action << endl;
	return out;
 }
 