#ifndef BLOCK_H_
#define BLOCK_H_

#include <set>

class Net;
class APEdge;
class Partition;

class Block {
public:
  Block(int idx);
  virtual ~Block();

private:
  int idx;
  std::set<Net *> nets;

  double x;
  double y;
  bool fixed;
  bool imaginary;

  std::set<APEdge *> apEdgesX;
  std::set<APEdge *> apEdgesY;

public:
  int getIdx() { return idx; }
  void addNet(Net *net);
  void setLoc(double x, double y) {
    this->x = x;
    this->y = y;
  }
  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
  double getX() { return x; }
  double getY() { return y; }
  void setFixed(bool fixed) { this->fixed = fixed; }
  bool isFixed() { return fixed; }
  void setImaginary(bool imaginary) { this->imaginary = imaginary; }
  bool isImaginary() { return imaginary; }

  std::set<APEdge *> &getApEdgesX() { return apEdgesX; }
  std::set<APEdge *> &getApEdgesY() { return apEdgesY; }
  void addApEdgeX(APEdge *edge);
  void addApEdgeY(APEdge *edge);
  void removeApEdgeX(APEdge *edge);
  void removeApEdgeY(APEdge *edge);
  double getApEdgeWeightX(Block *b);
  double getApEdgeWeightY(Block *b);
};

#endif