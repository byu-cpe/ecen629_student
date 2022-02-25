#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"
#include "Chromosome.h"
#include "Design.h"
#include "Net.h"
#include "utils.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: ./partitioner circuit_file seed\n");
    exit(-1);
  }

  // Seed RNG
  int rng_seed = std::stoi(argv[2]);

  Design design(rng_seed);

  // Open circuit file
  std::string filePath(argv[1]);
  std::ifstream fp(filePath);
  assert(fp.good());

  std::string line;
  int idx = 1;
  while (true) {
    if (!std::getline(fp, line))
      break;
    std::vector<std::string> words = split(line, ' ');

    auto wordIter = words.begin();
    Block *block = design.addBlock(idx++);
    wordIter++;

    for (; wordIter != words.end(); wordIter++) {
      int idx = std::stoi(*wordIter);
      Net *net = design.getOrCreateNet(idx);
      block->addNet(net);
      net->addBlock(block);
    }
  }

  printf("Num blocks: %d\n", design.getNumBlocks());
  printf("Num nets : %d\n", design.getNumNets());

  GeneticPartitioner partitioner(design);

  Chromosome *best = partitioner.getBestInPopulation();
  printf("Random population best solution cost: %d\n", best->getCost());

  design.genGraph(best, "initial");

  partitioner.run();

  best = partitioner.getBestInPopulation();
  best->recalcCutCost();
  printf("Solution is balanced: %s\n", best->isBalanced() ? "true" : "false");
  printf("Solution cost: %d\n", best->getCost());

  design.genGraph(best, "final");
}
