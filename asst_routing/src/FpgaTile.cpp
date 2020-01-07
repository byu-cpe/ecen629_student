/*
 * FpgaTile.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */

#include "FpgaTile.h"

#include "RRNode.h"
#include "easygl/graphics.h"

FpgaTile::FpgaTile(int r, int c, int W)
    : r(r), c(c), W(W), left(nullptr), right(nullptr), up(nullptr),
      down(nullptr) {
  // TODO Auto-generated constructor stub
}

FpgaTile::~FpgaTile() {
  // TODO Auto-generated destructor stub
}

void FpgaTile::generateContents() {
  // Add routing tracks
  if (down)
    for (int i = 0; i < W; i++) {
      RRNode *node = new RRNode(RRNode::V_WIRE, r, c, i);
      rrNodes.push_back(node);
      vWires.push_back(node);
    }
  if (right)
    for (int i = 0; i < W; i++) {
      RRNode *node = new RRNode(RRNode::H_WIRE, r, c, i);
      rrNodes.push_back(node);
      hWires.push_back(node);
    }

  if (down && right) {
    // Add logic pins
    logicPin[1] = new RRNode(RRNode::CB_WIRE, r, c, 1);
    logicPin[2] = new RRNode(RRNode::CB_WIRE, r, c, 2);
    logicPin[3] = new RRNode(RRNode::CB_WIRE, r, c, 1);
    logicPin[4] = new RRNode(RRNode::CB_WIRE, r, c, 2);

    rrNodes.push_back(logicPin[1]);
    rrNodes.push_back(logicPin[2]);
    rrNodes.push_back(logicPin[3]);
    rrNodes.push_back(logicPin[4]);

    // Add connection box
    for (int i = 0; i < W; i++) {
      vWires[i]->connect(*(logicPin[1]));
      vWires[i]->connect(*(logicPin[2]));
    }
    for (int i = 0; i < W; i++) {
      hWires[i]->connect(*(logicPin[3]));
      hWires[i]->connect(*(logicPin[4]));
    }
  }
}

void FpgaTile::populateSwitchbox() {
  if (up && down)
    for (int i = 0; i < W; i++)
      vWires[i]->connect(up->getVWire(i));

  if (left && right)
    for (int i = 0; i < W; i++)
      hWires[i]->connect(left->getHWire(i));

  if (left && up)
    for (int i = 0; i < W; i++)
      left->getHWire(i).connect(up->getVWire((W - i) % W));

  if (up && right)
    for (int i = 0; i < W; i++)
      up->getVWire(i).connect(this->getHWire((i + 1) % W));

  if (right && down)
    for (int i = 0; i < W; i++)
      this->getHWire(i).connect(this->getVWire((2 * W - 2 - i) % W));

  if (down && left)
    for (int i = 0; i < W; i++)
      this->getVWire(i).connect(left->getHWire((i + 1) % W));
}
