/*
 * Design.h
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include <map>
#include <string>
#include <vector>

class Net;
class RRNode;
class Net;

class Design {
public:
  Design();
  virtual ~Design();

private:
  // Nets in design
  std::vector<Net *> nets;

public:
  void addNet(Net &net);

  int getNumNets() { return nets.size(); }
  Net &getNet(int idx) { return *(nets[idx]); }

  std::vector<Net *> &getNets() { return nets; }
};

#endif /* DESIGN_H_ */
