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

int main(int argc, char **argv)
{
  std::string line;
  Design design;

  // Open the circuit file
  assert(argc == 2);
  std::string filePath(argv[1]);
  std::ifstream fp(filePath);
  assert(fp.good());

  getline(fp, line);
  design.setSize(std::stoi(line));

  while (true)
  {
    getline(fp, line);
    std::cout << "Line:" << line << "\n";
    if (line.size() == 0)
      break;

    // Get the block numbers
    std::istringstream iss(line);
    std::string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = std::stoi(sBlockIdx);
    Block *block = design.addBlock(blockIdx);

    std::string sNetNum;
    while (iss >> sNetNum)
    {
      int netIdx = stoi(sNetNum);
      std::cout << "Net " << netIdx << "\n";
      Net *net = design.getOrCreateNet(netIdx);
      block->addNet(net);
      net->addBlock(block);
    }
  }
  std::cout << "Number of blocks: " << design.getNumBlocks() << "\n";

  while (true)
  {
    getline(fp, line);
    if (line.size() == 0)
      break;
    std::istringstream iss(line);

    std::string sBlockIdx;
    iss >> sBlockIdx;
    int blockIdx = std::stoi(sBlockIdx);

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
  // design.analyticalPlacement();
  std::cout << "HPWL (after placement): " << design.calcHPWL() << "\n";
  Drawer::draw();
  Drawer::loop();
}
