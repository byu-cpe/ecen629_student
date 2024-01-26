/*
 * Net2.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#include <cassert>

#include "Block.h"
#include "Design.h"
#include "Net.h"

using namespace std;

Net::Net(Design &design, int idx) : design(design), idx(idx) {
  // TODO Auto-generated constructor stub
}

Net::~Net() {
  // TODO Auto-generated destructor stub
}

void Net::addBlock(Block *block) { blocks.push_back(block); }

int Net::calcHPWL() {
  int minX = design.getDevice().getSize();
  int minY = design.getDevice().getSize();
  int maxX = 0;
  int maxY = 0;

  for (auto b : blocks) {
    minX = min(minX, b->getX());
    maxX = max(maxX, b->getX());
    minY = min(minY, b->getY());
    maxY = max(maxY, b->getY());
  }
  return (maxX - minX) + (maxY - minY);
}
