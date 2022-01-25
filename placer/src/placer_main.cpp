#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Block.h"
#include "Design.h"
#include "Drawer.h"
#include "Net.h"
#include "easygl/graphics.h"

using namespace std;

int main(int argc, char **argv) {
  assert(argc == 2);

  string filePath(argv[1]);

  ifstream fp(filePath);
  assert(fp.good());

  string line;

  Design design;

  while (true) {
    getline(fp, line);
    istringstream iss(line);

    string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = stoi(sBlockIdx);

    if (blockIdx == -1)
      break;

    Block *block = design.addBlock(blockIdx);

    std::string sNetNum;
    while (true) {
      iss >> sNetNum;
      int netIdx = stoi(sNetNum);
      if (netIdx == -1)
        break;

      Net *net = design.getOrCreateNet(netIdx);
      block->addNet(net);
      net->addBlock(block);
    }
  }

  while (true) {
    getline(fp, line);
    istringstream iss(line);

    string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = stoi(sBlockIdx);

    if (blockIdx == -1)
      break;

    string sX, sY;
    iss >> sX;
    iss >> sY;

    int x = stoi(sX);
    int y = stoi(sY);
    Block *block = design.getBlock(blockIdx);
    block->setLoc(x, y);
    block->setFixed(true);
  }

  design.randomizeBlockLoc();

  Drawer::setDesign(&design);
  Drawer::init();
  Drawer::draw();
  cout << "HPWL (random placement): " << design.getHPWL() << "\n";
  Drawer::loop();

  design.analyticalPlacement();
}
