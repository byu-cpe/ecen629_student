#ifndef NET_H_
#define NET_H_

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
  std::set<APEdge *> apEdgesX;
  std::set<APEdge *> apEdgesY;

public:
  int getIdx() { return idx; }

  void addBlock(Block *block);
  std::vector<Block *> &getBlocks() { return blocks; }

  void createAPEdges();
  void deleteAPEdges();

  double getHPWL();
};

#endif