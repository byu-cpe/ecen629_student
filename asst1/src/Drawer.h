/*
 * Drawer.h
 *
 *  Created on: Dec 2, 2017
 *      Author: jgoeders
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include <map>

class FPGA;
class Net;
class RRNode;

class Drawer {
public:
  Drawer(FPGA *fpga);
  virtual ~Drawer();

private:
  static const int PAD = 10;
  static const int LB_SIZE = 50;
  static const int LB_GAP = 5;
  static const int WIRE_SPACING = 5;
  static const int NET_LINE_WIDTH = 5;

  static int getTileWidth(int W) {
    return (W * WIRE_SPACING + 2 * LB_GAP + LB_SIZE);
  }

  static FPGA *fpga;
  static std::map<Net *, int> netColors;
  static int nextNetColor;

  static int getColor(Net *net);
  static void setDrawNet(Net *net);

public:
  static void setFpga(FPGA &fpga) { Drawer::fpga = &fpga; }

  static void init();
  static void loop();
  static void draw();
  static void close();
};

#endif /* DRAWER_H_ */
