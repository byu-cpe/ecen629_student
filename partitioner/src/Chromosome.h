#ifndef SRC_CHROMOSOME
#define SRC_CHROMOSOME

#include <random>
#include <vector>

class Design;

class Chromosome {

public:
  Chromosome(Design &design);
  Chromosome(Chromosome *c1, Chromosome *c2, int cutpoint,
             bool complementC2 = false);
  ~Chromosome(){};

public:
  void setGeneIdx(int idx, bool val) { genes[idx] = val; }
  void shuffle_genes();
  int getCost() { return cutSize; }
  void print();
  bool isBalanced();
  void recalcCutCost();
  const std::vector<bool> &getGenes() { return genes; }

private:
  Design &design;
  std::vector<bool> genes;
  int cutSize;
  void balance();
  void flipBits(bool fromVal, int numTimes);
};

#endif /* SRC_CHROMOSOME */
