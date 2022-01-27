#ifndef BLOCK_H_
#define BLOCK_H_

#include <set>

class Net;
class APEdge;
class Partition;

// A Block in the Design
// This can be either a moveable block, a fixed block, or an imaginary block
// (used for extra movement constraints)
class Block {
public:
  // Create a block with a given idx value
  Block(int idx);

  virtual ~Block();

private:
  // Block idx value from netlist
  int idx;

   // Nets that this block is connected to
  std::set<Net *> nets;

  // X, Y location of block
  double x;
  double y;

  // Whether block is fixed (perimter I/O)
  bool fixed;

  // Whether block is imaginary
  bool imaginary;

  // Set of edges in X and Y direction that this block connects to
  std::set<APEdge *> apEdgesX;
  std::set<APEdge *> apEdgesY;

public:
  // Return block idx value
  int getIdx() { return idx; }

  // Add a new net to this block
  void addNet(Net *net);

  // Get/Set the block locations
  void setLoc(double x, double y) {
    this->x = x;
    this->y = y;
  }
  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
  double getX() { return x; }
  double getY() { return y; }

  // Set block properties
  void setFixed(bool fixed) { this->fixed = fixed; }
  bool isFixed() { return fixed; }
  void setImaginary(bool imaginary) { this->imaginary = imaginary; }
  bool isImaginary() { return imaginary; }

  // Get list of APEdges
  std::set<APEdge *> &getApEdgesX() { return apEdgesX; }
  std::set<APEdge *> &getApEdgesY() { return apEdgesY; }

  // Add or remove APEdge
  void addApEdgeX(APEdge *edge);
  void addApEdgeY(APEdge *edge);
  void removeApEdgeX(APEdge *edge);
  void removeApEdgeY(APEdge *edge);

  // Get APEdge weight that connects this block to block b.
  double getApEdgeWeightX(Block *b);
  double getApEdgeWeightY(Block *b);
};

#endif