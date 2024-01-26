#ifndef BLOCK_H_
#define BLOCK_H_

#include <set>

class Net;
class APEdge;
class Partition;
class Design;

// A Block in the Design
// This can be either a moveable block, a fixed block, or an imaginary block
// (used for extra movement constraints)
class Block {
public:
  // Create a block with a given idx value
  Block(Design &design, int idx);

  // Create a block at a constrained x,y location (I/O block)
  Block(Design &design, int idx, int x, int y);

  virtual ~Block();

  // Block cannot be moved or copied
  Block(const Block &) = delete;
  Block &operator=(const Block &) = delete;
  Block(Block &&) = default;            // Move constructor
  Block &operator=(Block &&) = default; // Move assignment operator

private:
  Design &design;

  // Block idx value from netlist
  int idx;

  // Nets that this block is connected to
  std::set<Net *> nets;

  // X, Y location of block
  int x;
  int y;

  // Whether block has been placed
  bool placed;

  // Whether block is fixed (perimter I/O)
  bool fixed;

  void unplace();

public:
  // Return block idx value
  int getIdx() { return idx; }

  // Add a new net to this block
  void addNet(Net *net);

  // Get/Set the block locations
  void place(int x, int y);
  void place(int xy);

  // Set block properties
  void setFixed(bool fixed) { this->fixed = fixed; }
  bool isFixed() { return fixed; }

  int getX() { return x; }
  int getY() { return y; }

private:
};

#endif