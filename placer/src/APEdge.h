#ifndef PLACER_SRC_APEDGE
#define PLACER_SRC_APEDGE

class Block;

/* AnalyticalPlacement Edge */
class APEdge {
public:
  // Create a new edge with given wieght, and add it to the list of X or Y edges
  // for Blocks a and b.
  APEdge(Block *a, Block *b, double weight, bool xNotY);
  virtual ~APEdge();

private:
  Block *a;
  Block *b;
  double weight;

public:
  void setWeight(float weight) { this->weight = weight; }
  double getWeight() { return weight; }

  // Given a block on the edge, return the other block
  Block *getOtherBlock(Block *b);

  Block *getA() { return a; }
  Block *getB() { return b; }
};

#endif /* PLACER_SRC_APEDGE */
