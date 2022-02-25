#ifndef PARTITIONER_SRC_DESIGN
#define PARTITIONER_SRC_DESIGN

#include <map>
#include <random>
#include <vector>

#include "GeneticPartitioner.h"

class Block;
class Net;
class Partition;

class Design {
public:
  Design(int rng_seed);
  virtual ~Design();

private:
  std::vector<Block *> blocks;
  std::map<int, Block *> block_map;
  std::vector<Net *> nets;
  std::default_random_engine rng;

  // Partition *rootPartition;

  // void partition_rec(bool draw, Partition *partialPartition,
  //                    std::vector<Block *>::iterator block,
  //                    Partition **bestSoln);

public:
  Block *addBlock(int idx);
  // void addBlock(Block *block) { blocks.push_back(block); }
  Block *getBlock(int idx) { return block_map[idx]; };

  Net *getOrCreateNet(int idx);
  void addNet(Net *net) { nets.push_back(net); }
  int getNumBlocks() { return blocks.size(); }
  std::vector<Block *> &getBlocks() { return blocks; }
  std::vector<Net *> &getNets() { return nets; }
  int getNumNets() { return nets.size(); }

  std::default_random_engine &getRng() { return rng; }

  void genGraph(Chromosome *c, std::string name);
  // Partition partition(bool draw);

  // float getTreeLevelHeight();

  // Partition *getRootPartition() { return rootPartition; }

  // void sortBlocks(bool desc);
};

#endif /* PARTITIONER_SRC_DESIGN */
