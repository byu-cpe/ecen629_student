#include "GeneticPartitioner.h"

#include <cassert>
#include <climits>

#include "Chromosome.h"
#include "Design.h"

GeneticPartitioner::GeneticPartitioner(Design &design) : design(design) {
  for (int i = 0; i < POPULATION_SIZE; i++) {
    Chromosome *c = new Chromosome(design);
    c->shuffle_genes();
    population.insert(c);
  }
  // printf("Population created with size %ld.\n", population.size());
  // for (auto p : population)
  //   p->print();
}

void GeneticPartitioner::run() {

  ////////////////////////////////////////////////
  // Step 1. Random population   /////////////////
  ////////////////////////////////////////////////

  ////////////////////////////////////////////////
  // Step 2. Choose 2 members to reproduce  //////
  ////////////////////////////////////////////////

  ////////////////////////////////////////////////
  // Step 3. Crossover  //////////////////////////
  ////////////////////////////////////////////////

  ////////////////////////////////////////////////
  // Step 4. (Optional) Mutation  ////////////////
  ////////////////////////////////////////////////

  ////////////////////////////////////////////////
  // Step 5. Reduce population back down  ////////
  ////////////////////////////////////////////////
}

void GeneticPartitioner::buildFitnessValues() {
  // Create and populate fitness values for entire population, stored in
  // fitnessValues
}

// Find and return the best chromosome in the population
Chromosome *GeneticPartitioner::getBestInPopulation() {
  Chromosome *best;

  int bestCost = INT_MAX;
  for (auto c : population) {
    if (c->getCost() < bestCost) {
      best = c;
      bestCost = c->getCost();
    }
  }
  return best;
}

// Get a random chromosome from the population based on the fitness values
Chromosome *GeneticPartitioner::chooseRandomByFitness() {}