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

#include "Block.h"
#include "Design.h"
#include "Drawer.h"
#include "Net.h"
#include "easygl/graphics.h"

using namespace std;

// const float Design::FPGA_SIZE = 100.0;

Design::Design(int deviceSize) : fpga(deviceSize) {
  // TODO Auto-generated constructor stub
}

Design::~Design() {}

Block *Design::addBlock(int idx) {
  Block *block = new Block(*this, idx);
  blocks.push_back(block);
  blockMap[idx] = block;
  return block;
}

Block *Design::addBlock(int idx, int x, int y) {
  Block *block = new Block(*this, idx, x, y);
  blocks.push_back(block);
  fpga.placeBlock(x, y, *block);
  blockMap[idx] = block;
  return block;
}

Net *Design::getOrCreateNet(int idx) {
  if (netMap.find(idx) != netMap.end()) {
    return netMap[idx];
  }

  Net *net = new Net(*this, idx);
  nets.push_back(net);
  netMap[idx] = net;
  return net;
}

int Design::calcHPWL() {
  int total = 0;
  for (auto n : nets) {
    total += n->calcHPWL();
  }
  return total;
}

Block *Design::getBlock(int idx) {
  if (blockMap.find(idx) == blockMap.end()) {
    return nullptr;
  }
  return blockMap[idx];
}

void Design::unplaceAllBlocks() {
  for (auto b : blocks) {
    if (b->isFixed())
      continue;
    b->unplace();
  }
}