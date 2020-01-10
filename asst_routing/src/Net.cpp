/*
 * Net.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <set>

#include "Net.h"
#include "RRNode.h"

using namespace std;

Net::Net(RRNode &source, int idx) : source(source), idx(idx) {}

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

bool Net::verifyRouting() {
  std::set<RRNode *> nodesReached;
  std::list<RRNode *> nodesToVisit;

  // Start expansion from source node
  if (source.getNet() != this) {
    std::cout << "***Net source " << source
              << " is not marked as belonging to net " << idx << "\n";
    return false;
  } else {
    nodesToVisit.push_back(&source);
  }

  // Expand routing
  while (nodesToVisit.size()) {
    RRNode *node = nodesToVisit.front();
    nodesToVisit.pop_front();
    nodesReached.insert(node);

    for (auto connection : node->getConnections()) {
      if (connection->getNet() == this &&
          (nodesReached.find(connection) == nodesReached.end())) {
        nodesToVisit.push_back(connection);
      }
    }
  }

  for (auto sink : sinks) {
    if (nodesReached.find(sink) == nodesReached.end()) {
      std::cout << "***Net " << idx << " with source " << source
                << " did not reach sink: " << *sink << "\n";
      return false;
    }
  }
  return true;
}