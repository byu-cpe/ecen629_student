#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "Design.h"
#include "Drawer.h"
#include "FPGA.h"
#include "FpgaTile.h"
#include "Net.h"
#include "RRNode.h"
#include "Router.h"
#include "easygl/graphics.h"
#include "utils.h"

using namespace std;

Drawer *drawer;

void drawscreen() { drawer->draw(); }

// Usage:
//    ./router [-d] [-p] <circuit_path> <W>
//
//  circuit_path: Path to text file describing design (FPGA size + netlist)
//  W:            Channel width
//
//  -d:           Enable display graphics
//  -p:           Print netlist while reading
int main(int argc, char **argv) {
  assert(argc == 3);

  bool display = false;
  bool printNets = false;

  // Get optional arguments
  int opt;
  while ((opt = getopt(argc, argv, "dp")) != -1) {
    switch (opt) {
    case 'd':
      display = true;
      break;
    case 'p':
      printNets = true;
      break;
    }
  }

  // Get positional arguments - there should be two, <circuit path> and <W>
  assert(argc - optind == 2);

  // Read circuit file
  std::string filePath(argv[optind++]);

  // Read channel width
  int W = stoi(argv[optind++]);

  ifstream fp(filePath);
  string line;

  // Get grid size
  getline(fp, line);
  trim(line);
  int gridSize = stoi(line) + 1;
  std::cout << "Grid size: " << gridSize << "x" << gridSize << "\n";

  // Get # tracks
  std::cout << "Number of tracks: " << W << "\n";

  // Initialize FPGA and design objects
  FPGA fpga(gridSize, W);
  Design design;

  // Get nets from circuit file
  int netIdx = 0;
  while (true) {
    getline(fp, line);
    trim(line);
    istringstream iss(line);

    // Read source
    string xStr, yStr, pStr;
    iss >> xStr;
    iss >> yStr;
    iss >> pStr;
    int x = stoi(xStr);
    int y = stoi(yStr);
    int p = stoi(pStr);

    if (x < 0)
      break;

    if (printNets)
      std::cout << "(" << x << ", " << y << ")." << p << " to ";
    Net *net = new Net(fpga.getTile(x, y).getLogicPin(p), netIdx++);

    // Read list of sinks
    while (iss >> xStr) {
      iss >> yStr;
      iss >> pStr;
      x = stoi(xStr);
      y = stoi(yStr);
      p = stoi(pStr);
      if (printNets)
        std::cout << "(" << x << ", " << y << ")." << p << " ";
      RRNode &sink = fpga.getTile(x, y).getLogicPin(p);
      net->addSink(sink);
    }
    if (printNets)
      cout << "\n";
    design.addNet(*net);
  }

  std::cout << "Starting Routing\n";

  if (display) {
    Drawer::setFpga(fpga);
    Drawer::init();
  }

  // Initialize router
  // Router *router = new MyRouter();
  // router->routeDesign(fpga, design);
  bool success = design.verifyRouting();
  if (!success) {
    std::cout << "Error: Routing not complete\n";
  } else {
    std::cout << "Routing check passed\n";
    std::cout << "Segments used: " << fpga.getNumSegmentsUsed() << "\n";
  }

  if (display) {
    Drawer::draw();
    Drawer::loop();
  }

  // delete router;

  return !success;
}
