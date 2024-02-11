#ifndef DESIGN_H_
#define DESIGN_H_

#include <map>
#include <vector>

#include "FPGA.h"

class Block;
class Net;

// Class representing the Design, with contains blocks, nets and methods for
// solving placement
class Design {
public:
  Design(int deviceSize);
  virtual ~Design();

  // const static float FPGA_SIZE;

private:
  // List of blocks and nets
  std::vector<Block *> blocks;
  std::vector<Net *> nets;
  FPGA fpga;
  std::map<int, Block *> blockMap;
  std::map<int, Net *> netMap;

public:
  FPGA &getDevice() { return fpga; }

  // Add a new block to the design
  Block *addBlock(int idx);
  // Add a fixed block to the design
  Block *addBlock(int idx, int x, int y);

  // Get a block by idx value
  Block *getBlock(int idx);

  // Get a net by idx value, or create it if it doesn't exist yet
  Net *getOrCreateNet(int idx);

  // Get nubmer of blocks
  int getNumBlocks() { return blocks.size(); }

  // Get list of blocks/nets
  std::vector<Block *> &getBlocks() { return blocks; }
  std::vector<Net *> &getNets() { return nets; }

  void setBlockLoc(Block *block, int x, int y);
  void setBlockLoc(Block *block, int xy);

  // Calculate the current half-perimiter wire length cost
  int calcHPWL();

  void unplaceAllBlocks();

  //////////////// You need to implement these functions ////////////////

  // Provide random placement of blocks
  void randomizePlacement(int seed);
  void simulatedAnnealing(int seed);

  // Perform greedy annealing
  void greedyAnnealing(int seed);

  void swapLocs(int xy1, int xy2);
};

#endif
