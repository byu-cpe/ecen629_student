/*
 * Drawer.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */
#include <algorithm>

#include "Drawer.h"

#include "FPGA.h"
#include "FpgaTile.h"
#include "Net.h"
#include "RRNode.h"
#include "easygl/graphics.h"

FPGA *Drawer::fpga = nullptr;
int Drawer::nextNetColor = (BLACK + 1);
std::map<Net *, int> Drawer::netColors;

using namespace std;

void act_on_mousebutton(float x, float y) {}
void act_on_keypress(char c) {}

Drawer::Drawer(FPGA *fpga) {}

Drawer::~Drawer() {
  // TODO Auto-generated destructor stub
}

void Drawer::init() {
  // TODO Auto-generated constructor stub

  init_graphics("Some Example Graphics", WHITE);

  // Set-up drawing coordinates. We choose from (xl,ybottom) = (0,0) to
  // (xr,ytop) = (1000,1000)
  int totalWidth = fpga->getN() * getTileWidth(fpga->getW());
  init_world(0., 0., 2 * PAD + totalWidth, 2 * PAD + totalWidth);

  // This message will show up at the bottom of the window.
  update_message("Interactive graphics example.");
}

void Drawer::loop() {
  event_loop(act_on_mousebutton, act_on_mousebutton, act_on_keypress,
             &(Drawer::draw));

  // close_graphics();
}

void Drawer::close() { close_graphics(); }

int Drawer::getColor(Net *net) {
  if (netColors.find(net) == netColors.end()) {
    netColors[net] = nextNetColor;
    nextNetColor++;
    if (nextNetColor == NUM_COLOR) {
      nextNetColor = (BLACK + 1);
    }
  }
  return netColors[net];
}

void Drawer::setDrawNet(Net *net) {
  if (net) {
    setcolor(getColor(net));
    setlinewidth(NET_LINE_WIDTH);
  } else {
    setcolor(BLACK);
    setlinewidth(1);
  }
}

void Drawer::draw() {
  clearscreen();
  //	setfontsize(36);
  //	setcolor(BLACK);
  //	drawtext(110,55, "colors", 150);

  FPGA *fpga = Drawer::fpga;

  int N = fpga->getN();
  int W = fpga->getW();
  for (int yIdx = 0; yIdx < N; yIdx++) {
    for (int xIdx = 0; xIdx < N; xIdx++) {
      int x = PAD + xIdx * getTileWidth(W);
      int y = PAD + yIdx * getTileWidth(W);

      FpgaTile &tile = fpga->getTile(xIdx, yIdx);

      // Draw vertical wires
      if (tile.getDown()) {
        for (int i = 0; i < W; i++) {
          int xW = x + WIRE_SPACING / 2.0 + i * WIRE_SPACING;
          int yW1 = y + W * WIRE_SPACING;
          int yW2 = y + W * WIRE_SPACING + 2 * LB_GAP + LB_SIZE;

          // Figure out if this is a partial wire going to a connection box
          // and which way it is going
          RRNode &rr = tile.getVWire(i);
          setDrawNet(nullptr);
          drawline(xW, yW1, xW, yW2);
          if (rr.getNet()) {
            bool up = false;
            bool down = false;
            bool partial = false;
            int idx;
            for (auto n : rr.getConnections()) {
              if (n->getNet() == rr.getNet()) {
                if (n->getType() == RRNode::CB_WIRE) {
                  partial = true;
                  idx = n->getIdx();
                } else if (n->getY() <= rr.getY())
                  up = true;
                else if (n->getY() > rr.getY())
                  down = true;
              }
            }
            if (up && down)
              partial = false;
            if (partial && up)
              yW2 = y + W * WIRE_SPACING + LB_GAP + LB_SIZE -
                    (idx * LB_SIZE / 3.0);
            else if (partial)
              yW1 = y + W * WIRE_SPACING + LB_GAP + LB_SIZE -
                    (idx * LB_SIZE / 3.0);

            setDrawNet(rr.getNet());
            drawline(xW, yW1, xW, yW2);
          }
        }
      }

      // Draw horizontal Wires
      if (tile.getRight()) {
        for (int i = 0; i < W; i++) {
          int xW1 = x + W * WIRE_SPACING;
          int xW2 = xW1 + 2 * LB_GAP + LB_SIZE;
          int yW = y + (W - 0.5 - i) * WIRE_SPACING;

          RRNode &rr = tile.getHWire(i);
          setDrawNet(nullptr);
          drawline(xW1, yW, xW2, yW);
          if (rr.getNet()) {
            bool left = false;
            bool right = false;
            bool partial = false;
            int idx;
            for (auto n : rr.getConnections()) {
              if (n->getNet() == rr.getNet()) {
                if (n->getType() == RRNode::CB_WIRE) {
                  partial = true;
                  idx = n->getIdx() - 2;
                } else if (n->getX() <= rr.getX())
                  left = true;
                else if (n->getX() > rr.getX())
                  right = true;
              }
            }
            if (left && right)
              partial = false;
            if (partial && left)
              xW2 = x + W * WIRE_SPACING + LB_GAP + idx * LB_SIZE / 3.0;
            else if (partial)
              xW1 = x + W * WIRE_SPACING + LB_GAP + idx * LB_SIZE / 3.0;

            setDrawNet(rr.getNet());
            drawline(xW1, yW, xW2, yW);
          }
        }
      }

      // Draw connection to logic block
      if (tile.getRight() && tile.getDown()) {
        Net *net;

        int xLB = x + W * WIRE_SPACING + LB_GAP;
        int yLB = y + W * WIRE_SPACING + LB_GAP;
        setDrawNet(nullptr);
        drawrect(xLB, yLB, xLB + LB_SIZE, yLB + LB_SIZE);

        // Draw Pin 1
        int xW1 = x + WIRE_SPACING / 2.0;
        int xW2 = x + W * WIRE_SPACING + LB_GAP;
        int yW = y + W * WIRE_SPACING + LB_GAP + 2 * LB_SIZE / 3.0;
        setDrawNet(nullptr);
        drawline(xW1, yW, xW2, yW);

        RRNode &rr1 = tile.getLogicPin(1);
        if (rr1.getNet()) {
          // Find which track this goes to
          for (auto n : rr1.getConnections()) {
            int idx = W;
            if (n->getNet() == rr1.getNet()) {
              idx = min(idx, n->getIdx());
              xW1 = x + (0.5 + idx) * WIRE_SPACING;
              setDrawNet(rr1.getNet());
              drawline(xW1, yW, xW2, yW);
            }
          }
        }

        // Draw Pin 2
        yW -= LB_SIZE / 3.0;
        setDrawNet(nullptr);
        drawline(xW1, yW, xW2, yW);

        RRNode &rr2 = tile.getLogicPin(2);
        if (rr2.getNet()) {
          // Find which track this goes to
          for (auto n : rr2.getConnections()) {
            int idx = W;
            if (n->getNet() == rr2.getNet()) {
              idx = min(idx, n->getIdx());
              xW1 = x + (0.5 + idx) * WIRE_SPACING;
              setDrawNet(rr2.getNet());
              drawline(xW1, yW, xW2, yW);
            }
          }
        }

        // Draw Pin 3
        int xW = x + W * WIRE_SPACING + LB_GAP + LB_SIZE / 3.0;
        int yW1 = y + WIRE_SPACING / 2.0;
        int yW2 = y + W * WIRE_SPACING + LB_GAP;
        setDrawNet(nullptr);
        drawline(xW, yW1, xW, yW2);

        RRNode &rr3 = tile.getLogicPin(3);
        if (rr3.getNet()) {
          // Find which track this goes to
          for (auto n : rr3.getConnections()) {
            int idx = 0;
            if (n->getNet() == rr3.getNet()) {
              idx = max(idx, n->getIdx());
              yW1 = y + (W - 0.5 - idx) * WIRE_SPACING;
              setDrawNet(rr3.getNet());
              drawline(xW, yW1, xW, yW2);
            }
          }
        }

        // Draw Pin 4
        xW += LB_SIZE / 3.0;
        setDrawNet(nullptr);
        drawline(xW, yW1, xW, yW2);

        RRNode &rr4 = tile.getLogicPin(4);
        if (rr4.getNet()) {
          // Find which track this goes to
          for (auto n : rr4.getConnections()) {
            int idx = 0;
            if (n->getNet() == rr4.getNet()) {
              idx = max(idx, n->getIdx());
              yW1 = y + (W - 0.5 - idx) * WIRE_SPACING;
              setDrawNet(rr4.getNet());
              drawline(xW, yW1, xW, yW2);
            }
          }
        }
      }

      if (tile.getUp() && tile.getDown())
        for (int i = 0; i < W; i++) {
          int xU = x + (i + 0.5) * WIRE_SPACING;
          int yU = y;
          int xD = xU;
          int yD = y + W * WIRE_SPACING;
          setDrawNet(tile.getUp()->getVWire(i).getNet() ==
                             tile.getVWire(i).getNet()
                         ? tile.getVWire(i).getNet()
                         : nullptr);
          drawline(xU, yU, xD, yD);
        }

      if (tile.getLeft() && tile.getRight())
        for (int i = 0; i < W; i++) {
          int xL = x;
          int yL = y + (W - i - 0.5) * WIRE_SPACING;
          int xR = x + W * WIRE_SPACING;
          int yR = yL;
          setDrawNet(tile.getLeft()->getHWire(i).getNet() ==
                             tile.getHWire(i).getNet()
                         ? tile.getHWire(i).getNet()
                         : nullptr);
          drawline(xL, yL, xR, yR);
        }

      if (tile.getLeft() && tile.getUp())
        for (int i = 0; i < W; i++) {
          int xU = x + (((W - i) % W) + 0.5) * WIRE_SPACING;
          int yU = y;
          int xL = x;
          int yL = y + (W - i - 0.5) * WIRE_SPACING;
          setDrawNet(tile.getLeft()->getHWire(i).getNet() ==
                             tile.getUp()->getVWire((W - i) % W).getNet()
                         ? tile.getLeft()->getHWire(i).getNet()
                         : nullptr);
          drawline(xU, yU, xL, yL);
        }

      if (tile.getUp() && tile.getRight())
        for (int i = 0; i < W; i++) {
          int xU = x + (0.5 + i) * WIRE_SPACING;
          int yU = y;
          int xR = x + W * WIRE_SPACING;
          int yR = y + (W - 0.5 - ((i + 1) % W)) * WIRE_SPACING;
          setDrawNet(tile.getUp()->getVWire(i).getNet() ==
                             tile.getHWire((i + 1) % W).getNet()
                         ? tile.getUp()->getVWire(i).getNet()
                         : nullptr);
          drawline(xU, yU, xR, yR);
        }

      if (tile.getRight() && tile.getDown())
        for (int i = 0; i < W; i++) {
          int xR = x + W * WIRE_SPACING;
          int yR = y + (W - 0.5 - i) * WIRE_SPACING;
          int xD = x + (0.5 + ((2 * W - 2 - i) % W)) * WIRE_SPACING;
          int yD = y + W * WIRE_SPACING;
          setDrawNet(tile.getHWire(i).getNet() ==
                             tile.getVWire((2 * W - 2 - i) % W).getNet()
                         ? tile.getHWire(i).getNet()
                         : nullptr);
          drawline(xR, yR, xD, yD);
        }

      if (tile.getDown() && tile.getLeft())
        for (int i = 0; i < W; i++) {
          int xD = x + (0.5 + i) * WIRE_SPACING;
          int yD = y + W * WIRE_SPACING;
          int xL = x;
          int yL = y + (W - 0.5 - ((i + 1) % W)) * WIRE_SPACING;
          setDrawNet(tile.getVWire(i).getNet() ==
                             tile.getLeft()->getHWire((i + 1) % W).getNet()
                         ? tile.getVWire(i).getNet()
                         : nullptr);
          drawline(xD, yD, xL, yL);
        }
    }
  }
}
