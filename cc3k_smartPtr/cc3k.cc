#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

#include "player.h"
#include "enemy.h"
#include "tile.h"

#include "textdisplay.h"
#include "floor.h"


bool dirIsValid(string dir) {
    if (dir == "no" || dir == "so" || dir == "ea" || dir == "we" || dir == "ne" || dir == "nw" || dir == "se" || dir == "sw") {
        return true;
    }
    return false;
}



int main(int argc, char* argv[]) {
    string filename;
    int seed;
    if (argc == 1) {
        filename = "floor.txt";
        srand(time(NULL));
    } else {
        filename = argv[1];
        if (argc == 3) {
            istringstream iss{argv[2]};
            iss >> seed;
            srand(seed);
        } else {
            srand(time(NULL));
        }
    }

    int level = 1;
    bool quit = false;
    bool restart = true;


    while (restart && !quit) {
        auto f = make_shared<Floor>(Floor{level});

        f->floorGenerator(filename);

        cout << "Now you need to choose the race you want to play with." << endl;
        cout << "[h]uman, [d]warf, [e]lves, [o]rc " << endl;
        char race;
        cin >> race;
        f->init(race, filename);
        cout << *f;
        bool nextFloor = false;
        bool live = true;


        while (true) {
            f->getDisplay()->clearAction();
            
            string command;
    	    cin >> command;
            if (command == "no" || command == "so" || command == "ea" || command == "we" || command == "ne" ||
                command == "nw" || command == "se" || command == "sw") {
                nextFloor = f->moverForPlayer(command);
               
            } else if (command == "u") {
                string dir;
    		    cin >> dir;
                if (dirIsValid(dir)) {
                    f->usePotion(dir);
                    
                } else {
                    cout << "Direction is valid. " << endl;
                }
    	    } else if (command == "a") {
    	    	string dir;
    		    cin >> dir;
                if (dirIsValid(dir)) {
                    f->playerAtk(dir);
                    
                } else {
                    cout << "Direction is valid. " << endl;
                }
    	    } else if (command == "help") {
                cout << "The command of this game is the follwoing: " << endl;
                cout << "no, so, ea, we, ne, nw, se, sw for the direction you want to move" << endl;
                cout << "u <direction> to using the positon indicated by the direction" << endl;
                cout << "a <direction> attacks the enemy indicated by the direction" << endl;
                cout << "q: exit the game" << endl;
                continue;
            } else if (command == "q") {
                quit = true;
                break;
            } else if (command == "buy"){
                string dir;
                cin >> dir;
                string potion;
                cin >> potion;
                if (dirIsValid(dir)) {
                    f->buyPotion(dir, potion);
                } else {
                    cout << "Direction is valid. " << endl;
                }

            } else {
                cout << "Invalid command. To see the command, please type help" << endl;
            }
            f->statusNotify();
            cout << *f;

            if (!f->playerIsAlive()) live = false;

            if (!live) break;

            if (nextFloor) {
                Player *clone = f->getPlayer()->createPlayer();
                shared_ptr<Player> play(clone);
                ++level;
                if (level <= 5) {
                    f = make_shared<Floor>(Floor{level});
                    f->floorGenerator(filename);
                    f->setPlayer(play);
                    f->init(race, filename);
                    f->statusNotify();
                    cout << *f;
                    nextFloor = false;
                } else {
                    cout << "Congradualation!! You win this game." << endl;
                    float score = f->getPlayer()->numGold();
                    if (f->getPlayer()->getName() == "human") score = score + score / 2;
                    cout << "Your final score is " << score  << endl;
                    quit = true;
                }
            }
        }

        if (!live) {                                                // the player is dead
            cout << "Unfortunately you lose this game. " << endl;
            float score = f->getPlayer()->numGold();
            if (f->getPlayer()->getName() == "human") score = score + score / 2;
            cout << "Your final score is " << score  << endl;
            quit = true;
        }


        if (quit) {
            cout << "You have quited this game. Do you want to restart? [r]estart/[n]o " << endl;
            char choice;
            cin >> choice;
            while (choice != 'R' && choice != 'r' && choice != 'N' && choice != 'n') {
                    cout << "Invalid! Please enter [r]estart/[N]o " << endl;
                    cin >> choice;
                }

            if (choice == 'R' || choice == 'r') {
                restart = true;
                quit = false;
                level = 1;
            } else {
                restart = false;
                quit = true;
            }
        }
    }
}
