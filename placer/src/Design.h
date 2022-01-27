#ifndef DESIGN_H_
#define DESIGN_H_

#include <map>
#include <vector>

class Block;
class Net;
class APEdge;

// Class representing the Design, with contains blocks, nets and methods for
// solving placement
class Design {
public:
  Design();
  virtual ~Design();

  const static float FPGA_SIZE;

private:
  // List of blocks and nets
  std::vector<Block *> blocks;
  std::vector<Net *> nets;

  void createApEdges();
  void removeApEdges();

public:
  // Add a new block to the design
  Block *addBlock(int idx);

  // Get a block by idx value
  Block *getBlock(int idx);

  // Get a net by idx value, or create it if it doesn't exist yet
  Net *getOrCreateNet(int idx);

  // Get nubmer of blocks
  int getNumBlocks() { return blocks.size(); }

  std::vector<Block *> &getBlocks() { return blocks; }
  std::vector<Net *> &getNets() { return nets; }

  // Provide random placement of blocks
  void randomizePlacement();

  // Solve analytical placement formulation and assign x,y values to each block
  void analyticalPlacement();

  // Perform legalization by spreading blocks out
  void legalizePlacement();

  // Calculate the current half-perimiter wire length cost
  double calcHPWL();

  // Calculate the Overlay cost
  int calcOverlay();

};

#endif
