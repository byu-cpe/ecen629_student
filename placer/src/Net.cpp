/*
 * Net2.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#include <cassert>

#include "APEdge.h"
#include "Block.h"
#include "Design.h"
#include "Net.h"

using namespace std;

Net::Net(int idx) : idx(idx) {
  // TODO Auto-generated constructor stub
}


Net::~Net() {
  // TODO Auto-generated destructor stub
}

void Net::addBlock(Block *block) {
  //	assert(blocks.find(block) == blocks.end());
  blocks.push_back(block);
}

void Net::createAPEdges() {
  int p = blocks.size();
  for (auto iter1 = blocks.begin(); iter1 != blocks.end(); ++iter1) {
    for (auto iter2 = next(iter1); iter2 != blocks.end(); ++iter2) {
      apEdgesX.insert(new APEdge(*iter1, *iter2, 2.0 / p, true));
      apEdgesY.insert(new APEdge(*iter1, *iter2, 2.0 / p, false));
    }
  }
}

void Net::deleteAPEdges() {
  for (auto e : apEdgesX) {
    e->getA()->removeApEdgeX(e);
    e->getB()->removeApEdgeX(e);
    delete (e);
  }
  apEdgesX.clear();

  for (auto e : apEdgesY) {
    e->getA()->removeApEdgeY(e);
    e->getB()->removeApEdgeY(e);
    delete (e);
  }
  apEdgesY.clear();
}

double Net::calcHPWL() {
  double minX = Design::FPGA_SIZE;
  double minY = Design::FPGA_SIZE;
  double maxX = 0;
  double maxY = 0;

  for (auto b : blocks) {
    if (b->isImaginary())
      continue;
    minX = min(minX, b->getX());
    maxX = max(maxX, b->getX());
    minY = min(minY, b->getY());
    maxY = max(maxY, b->getY());
  }
  return (maxX - minX) + (maxY - minY);
}
