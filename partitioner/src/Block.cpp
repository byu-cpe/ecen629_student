#include <algorithm>
#include <cassert>

#include "Block.h"

using namespace std;

Block::Block(int idx) : idx(idx) {}

Block::~Block() {
  // TODO Auto-generated destructor stub
}

void Block::addNet(Net *net) {
  assert(find(nets.begin(), nets.end(), net) == nets.end());
  nets.push_back(net);
}
