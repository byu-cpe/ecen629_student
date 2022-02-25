#ifndef PARTITIONER_SRC_NET
#define PARTITIONER_SRC_NET

#include <set>
#include <vector>

class Block;
class APEdge;

class Net {
public:
  Net(int idx);
  virtual ~Net();

private:
  int idx;
  std::vector<Block *> blocks;

public:
  int getIdx() { return idx; }

  void addBlock(Block *block);
  std::vector<Block *> &getBlocks() { return blocks; }
};

#endif /* PARTITIONER_SRC_NET */
