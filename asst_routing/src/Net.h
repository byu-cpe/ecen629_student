/*
 * Net.h
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#ifndef NET_H_
#define NET_H_

#include <set>

class RRNode;

class Net {
public:
  Net(RRNode &source, int idx);
  virtual ~Net();

private:
  RRNode &source;
  int idx;
  std::set<RRNode *> sinks;

  std::set<RRNode *> usedRRs;

public:
  void addSink(RRNode &dest);
  RRNode &getSource() { return source; }
  std::set<RRNode *> &getSinks() { return sinks; }
  void finalizeRouting();

  void clearPath() { usedRRs.clear(); }
  void addRRToPath(RRNode &node) { usedRRs.insert(&node); }
  std::set<RRNode *> &getPath() { return usedRRs; }
  int getIdx() { return idx; }
  bool verifyRouting();
};

#endif /* NET_H_ */
