/*
 * Design2.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

#include "APEdge.h"
#include "Block.h"
#include "Design.h"
#include "Drawer.h"
#include "Net.h"
#include "easygl/graphics.h"

#include <suitesparse/umfpack.h>

using namespace std;

const float Design::FPGA_SIZE = 100.0;

Design::Design() {
  // TODO Auto-generated constructor stub
}

Design::~Design() {
  // TODO Auto-generated destructor stub
}

Block *Design::addBlock(int idx) {
  Block *block = new Block(idx);
  assert(block != nullptr);
  blocks.push_back(block);
  return block;
}

Net *Design::getOrCreateNet(int idx) {
  for (auto n : nets) {
    if (n->getIdx() == idx)
      return n;
  }
  Net *net = new Net(idx);
  nets.push_back(net);
  return net;
}

void Design::randomizeBlockLoc() {
  for (auto b : blocks) {
    if (b->isFixed())
      continue;
    b->setLoc(rand() % ((int)FPGA_SIZE), rand() % ((int)FPGA_SIZE));
  }
}

float Design::getHPWL() {
  float total = 0;
  for (auto n : nets) {
    total += n->getHPWL();
  }
  return total;
}

void Design::createApEdges() {
  for (auto n : nets) {
    n->createAPEdges();
  }
}

void Design::removeApEdges() {
  for (auto n : nets) {
    n->deleteAPEdges();
  }
}

Block *Design::getBlock(int idx) {
  for (auto b : blocks)
    if (b->getIdx() == idx)
      return b;
  return nullptr;
}

void Design::analyticalPlacement() {
  createApEdges();

  // Build matrix

  // Solve matrix using UMF pack

  // Extract solution and set block x,y locations
}