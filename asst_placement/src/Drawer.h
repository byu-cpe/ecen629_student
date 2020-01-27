/*
 * Drawer2.h
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#ifndef ASST2_DRAWER_H_
#define ASST2_DRAWER_H_

class Design;
class Block;
class Net;

class Drawer {
public:
  const static int OUTSIDE_PAD = 10;
  const static int BLOCK_SIZE = 5;

  Drawer();
  virtual ~Drawer();

private:
  static Design *design;
  static void drawBlock(Block *block);
  static void drawNet(Net *net);

public:
  static void init();
  static void draw();
  static void loop();
  static void close();
  static void setDesign(Design *design) { Drawer::design = design; }
};

#endif /* ASST2_DRAWER_H_ */
