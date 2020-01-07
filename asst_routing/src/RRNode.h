/*
 * RRNode.h
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */

#ifndef RRNODE_H_
#define RRNODE_H_

#include <ostream>
#include <vector>

class RRNode;
class Net;

class RRNode {
public:
  enum rrType { H_WIRE, V_WIRE, CB_WIRE };
  const char *rrTypeStr[3] = {"H_WIRE", "V_WIRE", "CB_WIRE"};

  RRNode(rrType type, int r, int c, int idx = 0);
  virtual ~RRNode();

private:
  std::vector<RRNode *> connections;
  Net *net;
  rrType type;
  int r;
  int c;
  int idx;

public:
  void connect(RRNode &node);
  bool isConnected(RRNode &node);
  rrType getType() { return type; }
  int getR() { return r; }
  int getC() { return c; }
  int getIdx() { return idx; }

  bool isUsed() { return net != nullptr; }
  void setNet(Net &net);
  Net *getNet() { return net; }
  std::vector<RRNode *> &getConnections() { return connections; }

  friend std::ostream &operator<<(std::ostream &out, RRNode const &node) {
    out << "RRNode (" << node.r << ", " << node.c << ")."
        << node.rrTypeStr[node.type] << "." << node.idx;
    return out;
  }
};

#endif /* RRNODE_H_ */
