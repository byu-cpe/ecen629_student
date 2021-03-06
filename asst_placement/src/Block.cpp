/*
 * Block.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#include <cassert>

#include "APEdge.h"
#include "Block.h"

Block::Block(int idx) : idx(idx), x(0), y(0), fixed(false), imaginary(false) {
  // TODO Auto-generated constructor stub
}

Block::~Block() {
  // TODO Auto-generated destructor stub
}

void Block::addNet(Net *net) {
  assert(nets.find(net) == nets.end());
  nets.insert(net);
}

void Block::addApEdgeX(APEdge *edge) {
  assert(apEdgesX.find(edge) == apEdgesX.end());
  apEdgesX.insert(edge);
}

void Block::addApEdgeY(APEdge *edge) {
  assert(apEdgesY.find(edge) == apEdgesY.end());
  apEdgesY.insert(edge);
}

double Block::getApEdgeWeightX(Block *b) {
  for (auto e : apEdgesX) {
    if (e->getOtherBlock(this) == b)
      return e->getWeight();
  }
  return 0.;
}

double Block::getApEdgeWeightY(Block *b) {
  for (auto e : apEdgesY) {
    if (e->getOtherBlock(this) == b)
      return e->getWeight();
  }
  return 0.;
}

void Block::removeApEdgeX(APEdge *edge) { apEdgesX.erase(edge); }

void Block::removeApEdgeY(APEdge *edge) { apEdgesY.erase(edge); }
