#ifndef _TILE_H_
#define _TILE_H_

#include "object.h"
#include <vector>
#include <utility>
#include <string>


class Tile: public Object {
  bool occupied = false;
  int chamberIndex;
  Object *ob = nullptr;
  std::vector <std::pair<std::string, Tile *>> neighbor;
 public:

  Tile(int x, int y, int chamberIndex);
  bool isOccupied();                           // return true if the tile is occupied
  int chamberNum();
  void putObject(Object *obj);                 // put the object obj onto the tile
  void emptied();                              // remove the object from the tile
  void addNeighbor(std::string direction, Tile *t);  // add a neighbor to the tile
  unsigned int neighborSize();
  Object *item();                              // return the object on the tile
  Tile *getNeighbor(int index);                  // return a pointer to a neighbor
  ~Tile();
};

#endif
