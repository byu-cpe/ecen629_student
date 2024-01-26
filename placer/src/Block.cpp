#include <cassert>
#include <iostream>

#include "Block.h"
#include "Design.h"
#include "Net.h"

Block::Block(Design &design, int idx)
    : design(design), idx(idx), x(0), y(0), fixed(false), placed(false) {
  // TODO Auto-generated constructor stub
}

Block::Block(Design &design, int idx, int x, int y)
    : design(design), idx(idx), x(x), y(y), fixed(true), placed(true) {}

Block::~Block() {
  // TODO Auto-generated destructor stub
}

void Block::addNet(Net *net) {
  if (nets.find(net) != nets.end()) {
    std::cout << "Block " << idx << " already has net " << net->getIdx()
              << std::endl;
    assert(false);
  }
  assert(nets.find(net) == nets.end());
  nets.insert(net);
}

void Block::unplace() {
  assert(!fixed);
  assert(placed);

  this->placed = false;
  design.getDevice().unplaceBlock(x, y);
}

void Block::place(int x, int y) {
  assert(!fixed);
  assert(!placed);

  this->x = x;
  this->y = y;
  design.getDevice().placeBlock(x, y, *this);
}

void Block::place(int xy) {
  int size = design.getDevice().getSize();
  place(xy % size, xy / size);
}
