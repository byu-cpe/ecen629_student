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

int main(int argc, char **argv) {
  assert(argc == 2);

  std::string filePath(argv[1]);

  std::ifstream fp(filePath);
  assert(fp.good());

  std::string line;

  Design design;

  while (true) {
    getline(fp, line);
    std::istringstream iss(line);

    std::string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = std::stoi(sBlockIdx);

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
    std::istringstream iss(line);

    std::string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = std::stoi(sBlockIdx);

    if (blockIdx == -1)
      break;

    std::string sX, sY;
    iss >> sX;
    iss >> sY;

    int x = std::stoi(sX);
    int y = std::stoi(sY);
    Block *block = design.getBlock(blockIdx);
    block->setLoc(x, y);
    block->setFixed(true);
  }

  design.randomizePlacement();

  Drawer::setDesign(&design);
  Drawer::init();
  Drawer::draw();
  flushinput();
  std::cout << "HPWL (random placement): " << design.calcHPWL() << "\n";
  Drawer::loop();

  // Perform analytical placement
  design.analyticalPlacement();
  std::cout << "HPWL (after AP): " << design.calcHPWL() << "\n";
  Drawer::draw();
  Drawer::loop();

  design.legalizePlacement();

  // Print results
  std::cout << "HPWL (after legalization): " << design.calcHPWL() << "\n";
  std::cout << "Overlay: " << design.calcOverlay() << "\n";
  Drawer::draw();
  Drawer::loop();
}
