/*
 * FPGA.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: jgoeders
 */

#include "FPGA.h"
#include "FpgaTile.h"

FPGA::FPGA(int gridSize, int W) : N(gridSize), W(W) {

  // Create all tiles
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      FpgaTile *tile = new FpgaTile(r, c, W);
      tiles.push_back(tile);
      tileMap[r][c] = tile;
    }
  }

  for (auto tile : tiles) {
    int r = tile->getR();
    int c = tile->getC();
    if (r != 0)
      tileMap[r][c]->setUp(tileMap[r - 1][c]);
    if (r != (N - 1))
      tileMap[r][c]->setDown(tileMap[r + 1][c]);
    if (c != 0)
      tileMap[r][c]->setLeft(tileMap[r][c - 1]);
    if (c != (N - 1))
      tileMap[r][c]->setRight(tileMap[r][c + 1]);
  }

  for (auto tile : tiles) {
    tile->generateContents();
  }

  for (auto tile : tiles) {
    tile->populateSwitchbox();
  }
}

FPGA::~FPGA() {
  // TODO Auto-generated destructor stub
}
