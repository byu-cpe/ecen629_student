#include <iostream>

#include "Design.h"
#include "FPGA.h"
#include "Net.h"
#include "RRNode.h"
#include "Router.h"

Router::Router() {}

Router::~Router() {}

void Router::routeDesign(FPGA &fpga, Design &design) {
  std::cout << "Implement your router here\n";

  Net &net = design.getNet(0);
  std::cout << net.getSource() << "\n";
}