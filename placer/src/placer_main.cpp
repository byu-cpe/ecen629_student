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

  assert(argc >= 2);

  bool display = false;

  // Get optional arguments
  int opt;
  while ((opt = getopt(argc, argv, "d")) != -1) {
    switch (opt) {
    case 'd':
      display = true;
      break;
    }
  }

  // Get positional arguments - there should be one: <circuit path>
  assert(argc - optind == 1);

  // Read circuit file
  std::string filePath(argv[optind++]);

  // Open the circuit file
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

    Block *block = design.addBlock(blockIdx, x, y);
  }

  while (true) {
    getline(fp, line);
    if (line.size() == 0)
      break;

    // Get the block numbers
    std::istringstream iss(line);
    int blockIdx;
    iss >> blockIdx;
    Block *block = design.getBlock(blockIdx);
    if (!block) {
      block = design.addBlock(blockIdx);
    }

    int netIdx;
    while (iss >> netIdx) {
      Net *net = design.getOrCreateNet(netIdx);
      assert(net);
      net->addBlock(block);
    }
  }

  std::cout << "Number of blocks: " << design.getNumBlocks() << "\n";

  // Perform random placement
  std::cout << "Performing random placement\n";
  design.randomizePlacement(0);
  std::cout << "HPWL (random placement): " << design.calcHPWL() << "\n";
  if (display) {
    Drawer::setDesign(design);
    Drawer::init();
    Drawer::draw();
    Drawer::loop();
  }

  // Perform analytical placement
  design.greedyAnnealing(0);

  std::cout << "HPWL (after greedy annealing): " << design.calcHPWL() << "\n";
  if (display) {
    Drawer::draw();
    Drawer::loop();
  }

  design.unplaceAllBlocks();
  design.randomizePlacement(0);

  design.simulatedAnnealing(0);
  std::cout << "HPWL (after simulated annealing): " << design.calcHPWL()
            << "\n";

  if (display) {
    Drawer::draw();
    Drawer::loop();
  }
}
