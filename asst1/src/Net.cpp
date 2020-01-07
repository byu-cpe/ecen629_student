/*
 * Net.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#include <algorithm>
#include <cassert>

#include "Net.h"
#include "RRNode.h"

using namespace std;

Net::Net(RRNode &source) : source(source) {}

Net::~Net() {
  // TODO Auto-generated destructor stub
}

void Net::addSink(RRNode &dest) {
  // Make sure it isn't aleady in there
  assert(find(sinks.begin(), sinks.end(), &dest) == sinks.end());

  sinks.insert(&dest);
}

void Net::finalizeRouting() {
  for (auto node : usedRRs) {
    node->setNet(*this);
  }
}
