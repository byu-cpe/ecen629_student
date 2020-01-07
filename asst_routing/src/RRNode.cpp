/*
 * RRNode.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */

#include <algorithm>
#include <cassert>
#include <ostream>

#include "RRNode.h"

using namespace std;

RRNode::RRNode(rrType type, int r, int c, int idx)
    : net(nullptr), type(type), r(r), c(c), idx(idx) {
  // TODO Auto-generated constructor stub
}

RRNode::~RRNode() {
  // TODO Auto-generated destructor stub
}

void RRNode::connect(RRNode &node) {
  assert(!isConnected(node));
  assert(!node.isConnected(*this));

  connections.push_back(&node);
  node.connections.push_back(this);
}

bool RRNode::isConnected(RRNode &node) {
  return find(connections.begin(), connections.end(), &node) !=
         connections.end();
}

void RRNode::setNet(Net &net) {
  assert(this->net == nullptr);
  this->net = &net;
}