/*
 * Design2.h
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include <map>
#include <vector>

class Block;
class Net;
class APEdge;

class Design {
public:
  Design();
  virtual ~Design();

  const static float FPGA_SIZE;

private:
  std::vector<Block *> blocks;
  std::vector<Net *> nets;

  void createApEdges();
  void removeApEdges();

public:
  Block *addBlock(int idx);
  Block *getBlock(int idx);
  Net *getOrCreateNet(int idx);
  int getNumBlocks() { return blocks.size(); }
  void randomizeBlockLoc();
  std::vector<Block *> &getBlocks() { return blocks; }
  std::vector<Net *> &getNets() { return nets; }

  void analyticalPlacement();
  double calcHPWL();
  double calcOverlay();
};

#endif
