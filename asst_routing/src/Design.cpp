/*
 * Design.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#include <iostream>
#include <list>
#include <set>

#include "Design.h"

#include "Net.h"
#include "RRNode.h"

using namespace std;

Design::Design() {}

Design::~Design() {
  // TODO Auto-generated destructor stub
}

// Add a new net to the design
void Design::addNet(Net &net) {

  if (net.getSinks().size() == 0) {
    std::cout << "Adding net to design with no sinks\n";
    exit(-1);
  }

  std::set<RRNode *> nodes;

  for (auto existing_net : nets) {
    nodes.insert(&(existing_net->getSource()));
    for (auto dest : existing_net->getSinks()) {
      nodes.insert(dest);
    }
  }

  if (nodes.find(&(net.getSource())) != nodes.end()) {
    std::cout << "Adding net to design with conflicting source pin "
              << net.getSource() << "\n";
    exit(-1);
  }
  for (auto sink : net.getSinks()) {
    if (nodes.find(sink) != nodes.end()) {
      std::cout << "Adding net to design with conflicting sink pin " << *sink
                << "\n";
      exit(-1);
    }
  }

  nets.push_back(&net);
}

bool Design::verifyRouting() {
  // Check that each net can route successfully
  for (auto net : nets) {
    // std::cout << "Checking net\n";

    bool success = net->verifyRouting();
    if (!success)
      return false;
  }
  return true;
}