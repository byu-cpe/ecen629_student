#ifndef NET_H_
#define NET_H_

#include <set>
#include <vector>

class Block;

// Class representing a Net in the design
class Net {
public:
  // Create a net with given idx value
  Net(Design &design, int idx);

  virtual ~Net();

  // Net cannot be copied
  Net(const Net &) = delete;
  Net &operator=(const Net &) = delete;
  Net(Net &&) = default;            // Move constructor
  Net &operator=(Net &&) = default; // Move assignment operator

private:
  Design &design;

  // Net idx value for real nets
  int idx;

  // List of blocks this Net connects to
  std::vector<Block *> blocks;

public:
  // Return the net idx value
  int getIdx() { return idx; }

  // Add a block to the Net
  void addBlock(Block *block);

  // Get a list of blocks this Net connects to
  std::vector<Block *> &getBlocks() { return blocks; }

  // Calculate the half-perimeter wire length for this Net
  int calcHPWL();

private:
};

#endif