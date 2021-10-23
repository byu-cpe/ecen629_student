/*
 * FpgaTile.h
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */

#ifndef FPGATILE_H_
#define FPGATILE_H_

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

class RRNode;

class FpgaTile {
public:
  FpgaTile(int r, int c, int W);
  virtual ~FpgaTile();

private:
  int x;
  int y;
  int W;

  FpgaTile *left;
  FpgaTile *right;
  FpgaTile *up;
  FpgaTile *down;

  std::map<int, RRNode *> logicPin;
  std::vector<RRNode *> vWires;
  std::vector<RRNode *> hWires;

  std::vector<RRNode *> rrNodes;

public:
  int getX() { return x; }
  int getY() { return y; }

  std::vector<RRNode *> &getRRNodes() { return rrNodes; }

  FpgaTile *getDown() const { return down; }

  void setDown(FpgaTile *down) { this->down = down; }

  FpgaTile *getLeft() const { return left; }

  void setLeft(FpgaTile *left) { this->left = left; }

  FpgaTile *getRight() const { return right; }

  void setRight(FpgaTile *right) { this->right = right; }

  FpgaTile *getUp() const { return up; }

  void setUp(FpgaTile *up) { this->up = up; }

  void generateContents();
  void populateSwitchbox();

  RRNode &getLogicPin(int idx) {
    // std::cout << idx << "\n";
    assert(logicPin.find(idx) != logicPin.end());
    return *(logicPin[idx]);
  }

  RRNode &getVWire(int idx) {
    assert(idx < vWires.size());
    return *(vWires[idx]);
  }

  RRNode &getHWire(int idx) {
    assert(idx < hWires.size());
    return *(hWires[idx]);
  }
};

#endif /* FPGATILE_H_ */
