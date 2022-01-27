#ifndef NET_H_
#define NET_H_

#include <set>
#include <vector>

class Block;
class APEdge;

// Class representing a Net in the design
class Net {
public:
  // Create a net with given idx value
  Net(int idx);

  virtual ~Net();

private:
  // Net idx value for real nets
  int idx;

  // List of blocks this Net connects to
  std::vector<Block *> blocks;

  // List of APEdges in X and Y dimension for this Net
  std::set<APEdge *> apEdgesX;
  std::set<APEdge *> apEdgesY;

public:
  // Return the net idx value
  int getIdx() { return idx; }

  // Add a block to the Net
  void addBlock(Block *block);

  // Get a list of blocks this Net connects to
  std::vector<Block *> &getBlocks() { return blocks; }

  // Create/Delete APEdges that represent this Net
  void createAPEdges();
  void deleteAPEdges();

  // Calculate the half-perimeter wire length for this Net
  double calcHPWL();
};

#endif