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

// Main takes 2 command-line arguments:
// 1 - path to circuit file
// 2 - channel width to attempt
int main(int argc, char **argv) {
  assert(argc == 3);

  // Read circuit file
  std::string filePath(argv[1]);
  ifstream fp(filePath);
  string line;

  // Get grid size
  getline(fp, line);
  trim(line);
  int gridSize = stoi(line) + 1;
  std::cout << "Grid size: " << gridSize << "x" << gridSize << "\n";

  // Get # tracks
  int W = stoi(argv[2]);
  std::cout << "Number of tracks: " << W << "\n";

  // Initialize FPGA and design objects
  FPGA fpga(gridSize, W);
  Design design;

  // Get nets from circuit file
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

    std::cout << "(" << x << ", " << y << ")." << p << " to ";
    Net *net = new Net(fpga.getTile(x, y).getLogicPin(p));

    // Read list of sinks
    while (iss >> xStr) {
      iss >> yStr;
      iss >> pStr;
      x = stoi(xStr);
      y = stoi(yStr);
      p = stoi(pStr);
      std::cout << "(" << x << ", " << y << ")." << p << " ";
      RRNode &sink = fpga.getTile(x, y).getLogicPin(p);
      net->addSink(sink);
    }
    cout << "\n";
    design.addNet(*net);
  }

  std::cout << "Starting Routing\n";

  // Initialize router
  Router router;

  Drawer::setFpga(fpga);
  Drawer::init();

  while (1) {
    router.routeDesign(fpga, design);
    Drawer::draw();
    Drawer::loop();
  }
}
