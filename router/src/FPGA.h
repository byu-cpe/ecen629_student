/*
 * FPGA.h
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#ifndef FPGA_H_
#define FPGA_H_

#include <map>
#include <vector>

class FpgaTile;

class FPGA {
public:
  FPGA(int gridSize, int W);
  virtual ~FPGA();

private:
  int N;
  int W;

  // There are NxN tiles
  std::map<int, std::map<int, FpgaTile *>> tileMap;

  // List of all tiles
  std::vector<FpgaTile *> tiles;

public:
  FpgaTile &getTile(int x, int y) { return *(tileMap[x][y]); }
  std::vector<FpgaTile *> &getTiles() { return tiles; }

  int getN() { return N; }
  int getW() { return W; }
  int getNumSegmentsUsed();
};

#endif /* FPGA_H_ */
