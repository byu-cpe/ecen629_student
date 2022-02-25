#ifndef SRC_GENETICPARTITIONER
#define SRC_GENETICPARTITIONER

#include <map>
#include <set>

class Design;
class Chromosome;

class GeneticPartitioner {
public:
  static const int POPULATION_SIZE = 50;

  GeneticPartitioner(Design &design);
  ~GeneticPartitioner(){};

  void run();
  Chromosome *getBestInPopulation();

private:
  Design &design;
  std::set<Chromosome *> population;

  void buildFitnessValues();
  std::map<Chromosome *, float> fitnessValues;
  Chromosome *chooseRandomByFitness();
};

#endif /* SRC_GENETICPARTITIONER */
