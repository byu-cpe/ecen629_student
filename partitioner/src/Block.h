#ifndef PARTITIONER_SRC_BLOCK
#define PARTITIONER_SRC_BLOCK

#include <vector>

class Net;
class APEdge;
class Partition;

class Block {
public:
  Block(int idx);
  virtual ~Block();

private:
  int idx;

  std::vector<Net *> nets;

public:
  int getIdx() { return idx; }
  void addNet(Net *net);
  std::vector<Net *> &getNets() { return nets; }

  // bool operator<(const Block &other) const {
  //   return nets.size() < other.nets.size();
  // }
  // bool operator>(const Block &other) const {
  //   return nets.size() > other.nets.size();
  // }
};

#endif /* PARTITIONER_SRC_BLOCK */
