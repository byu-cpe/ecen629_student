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
  std::string line;

  // Open the circuit file
  assert(argc == 2);
  std::string filePath(argv[1]);
  std::ifstream fp(filePath);
  assert(fp.good());

  getline(fp, line);

  Design design(std::stoi(line));

  // Get the fixed I/O blocks
  while (true) {
    getline(fp, line);
    if (line.size() == 0)
      break;
    std::istringstream iss(line);

    int blockIdx;
    int x, y;
    iss >> blockIdx >> x >> y;

    printf("New block %d at %d %d\n", blockIdx, x, y);

    Block *block = design.addBlock(blockIdx, x, y);
  }

  while (true) {
    getline(fp, line);
    std::cout << "Line:" << line << "\n";
    if (line.size() == 0)
      break;

    // Get the block numbers
    std::istringstream iss(line);
    int blockIdx;
    iss >> blockIdx;
    Block *block = design.getBlock(blockIdx);
    if (!block) {
      std::cout << "Block " << blockIdx << " not found\n";
      block = design.addBlock(blockIdx);
    }

    int netIdx;
    while (iss >> netIdx) {
      std::cout << "Net " << netIdx << "\n";
      Net *net = design.getOrCreateNet(netIdx);
      assert(net);
      net->addBlock(block);
    }
  }

  Drawer::setDesign(design);
  Drawer::init();
  std::cout << "Number of blocks: " << design.getNumBlocks() << "\n";
  Drawer::draw();
  flushinput();
  design.randomizePlacement();
  std::cout << "HPWL (random placement): " << design.calcHPWL() << "\n";
  Drawer::loop();

  // Perform analytical placement
  // design.analyticalPlacement();
  std::cout << "HPWL (after placement): " << design.calcHPWL() << "\n";
  Drawer::draw();
  Drawer::loop();
  // Perform analytical placement
  // Perform analytical placement
  Drawer::draw();
  Drawer::loop();
}
