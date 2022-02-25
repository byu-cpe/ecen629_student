#include "Chromosome.h"

#include <algorithm>
#include <random>

#include "Block.h"
#include "Design.h"
#include "Net.h"

Chromosome::Chromosome(Design &design)
    : design(design), genes(design.getNumBlocks(), false) {
  // Create balance of true/false
  for (int i = 0; i < genes.size() / 2; i++)
    setGeneIdx(i, true);
  recalcCutCost();
};

Chromosome::Chromosome(Chromosome *c1, Chromosome *c2, int cutpoint,
                       bool complementC2)
    : design(c1->design), genes(c1->genes.size(), false) {

  // Create new child chromosome from two parent chromosomes
  // See details in Bui paper.
}

bool Chromosome::isBalanced() {
  int cnt0 = 0;
  int cnt1 = 0;
  for (bool g : genes) {
    g ? cnt1++ : cnt0++;
  }

  return ((cnt1 - cnt0) <= 1) && ((cnt1 - cnt0) >= -1);
}

void Chromosome::balance() {
  // Need to balance 0s and 1s
}

// Randomly flip some bits from 0 to 1 or 1 to 0
// fromBit: bit to flip from.  ie, when false, flip 0 to 1.
// numTimes: how many bits to flip
void Chromosome::flipBits(bool fromBit, int numTimes) {}

void Chromosome::shuffle_genes() {
  shuffle(std::begin(genes), std::end(genes), design.getRng());
  recalcCutCost();
}

// Recalculate the cut cost that is stored and cached in cutSize.
void Chromosome::recalcCutCost() {
  cutSize = 0;
  for (auto n : design.getNets()) {
    bool part0 = false;
    bool part1 = false;
    for (auto b : n->getBlocks()) {
      if (genes[b->getIdx()])
        part1 = true;
      else
        part0 = true;

      if (part0 && part1) {
        cutSize++;
        break;
      }
    }
  }
}

void Chromosome::print() {
  for (bool g : genes) {
    printf("%d", g ? 1 : 0);
  }
  printf("\n");
}