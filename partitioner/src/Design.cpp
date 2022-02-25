#include "Design.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

#include "Block.h"
#include "Chromosome.h"
#include "Net.h"

Design::Design(int rng_seed) { rng.seed(rng_seed); }

Design::~Design() {}

Block *Design::addBlock(int idx) {
  if (block_map.find(idx) != block_map.end()) {
    printf("Design already contains block with index %d\n", idx);
    assert(false);
  }
  Block *block = new Block(idx);
  blocks.push_back(block);
  block_map[idx] = block;
  return block;
}

Net *Design::getOrCreateNet(int idx) {
  for (auto n : nets) {
    if (n->getIdx() == idx)
      return n;
  }
  Net *net = new Net(idx);
  nets.push_back(net);
  return net;
}

void Design::genGraph(Chromosome *c, std::string name) {
  std::ofstream fp;
  fp.open(name + ".dot");
  fp << "graph test {\n";
  fp << "\trankdir=\"LR\";\n";
  fp << "\tsplines=false;\n";

  auto genes = c->getGenes();
  fp << "subgraph cluster_left {\n";
  for (int i = 0; i < getNumBlocks(); i++)
    if (!genes[i])
      fp << "\t" << i << "\n";
  fp << "}\n";

  fp << "subgraph cluster_right {\n";
  for (int i = 0; i < getNumBlocks(); i++)
    if (genes[i])
      fp << "\t" << i << "\n";
  fp << "}\n";

  for (auto n : nets) {
    bool netDrawn = false;
    for (auto b1 : n->getBlocks()) {
      for (auto b2 : n->getBlocks()) {
        // Check if b1 on left and b2 on right
        if (!genes[b1->getIdx()] && genes[b2->getIdx()]) {
          fp << "\t" << b1->getIdx() << " -- " << b2->getIdx() << ";\n";
          netDrawn = true;
          break;
        }
      }
      if (netDrawn)
        break;
    }
  }

  fp << "}\n";

  fp.close();
}
