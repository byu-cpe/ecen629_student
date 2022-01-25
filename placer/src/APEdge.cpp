#include <cassert>
#include <cmath>
#include <iostream>

#include "APEdge.h"
#include "Block.h"

using namespace std;

APEdge::~APEdge() {}

APEdge::APEdge(Block *a, Block *b, double weight, bool xNotY)
    : a(a), b(b), weight(weight) {
  if (xNotY) {
    a->addApEdgeX(this);
    b->addApEdgeX(this);
  } else {
    a->addApEdgeY(this);
    b->addApEdgeY(this);
  }
}

Block *APEdge::getOtherBlock(Block *block) {
  if (a == block)
    return b;
  else if (b == block)
    return a;

  assert(false);
  return NULL;
}
