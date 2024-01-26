#include "FPGA.h"

#include <cassert>

#include "Block.h"

void FPGA::placeBlock(int x, int y, Block &block) {
  assert(blockMap.find(std::make_pair(x, y)) == blockMap.end());
  blockMap[std::make_pair(x, y)] = &block;
}
void FPGA::unplaceBlock(int x, int y) {
  assert(blockMap.find(std::make_pair(x, y)) != blockMap.end());
  blockMap.erase(std::make_pair(x, y));
}