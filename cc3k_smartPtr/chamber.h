#ifndef _CHAMBER_H_
#define _CHAMBER_H_

#include <vector>

class Tile;

class Chamber {
  std::vector <Tile *> member;
  int index;              // 0, 1, 2, 3, 4
  int size = 0;
 public:
  Chamber(int index);
  ~Chamber();
  void addTile(Tile *t);   // add a tile to the chamber
  void addNeighbor(Tile *t);       // add neighbor the the Tile *t
  Tile *getTile(int num);
  int getIndex();
  int getSize();          // return the number of tile in the chamber
};

#endif
