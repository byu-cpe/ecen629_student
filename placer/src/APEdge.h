#ifndef APEDGE_H_
#define APEDGE_H_

class Block;

class APEdge {
public:
  APEdge(Block *a, Block *b, double weight, bool xNotY);
  virtual ~APEdge();

private:
  Block *a;
  Block *b;
  double weight;

public:
  void setWeight(float weight) { this->weight = weight; }
  double getWeight() { return weight; }

  Block *getOtherBlock(Block *b);

  Block *getA() { return a; }
  Block *getB() { return b; }
};

#endif
