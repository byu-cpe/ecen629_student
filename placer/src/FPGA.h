#include <map>

class Block;

class FPGA {
public:
  FPGA(int size) : size(size) {}
  ~FPGA() {}

  // Get the size of the FPGA (one side of square)
  int getSize() { return size; }

  // Place a block at a given location
  void placeBlock(int x, int y, Block &block);

  // Remove a block from a given location
  void unplaceBlock(int x, int y);

  // Get the block at a given location
  Block *getBlock(int x, int y);
  Block *getBlock(int xy) { return getBlock(xy % size, xy / size); }

  // Check if a given location is for fixed IO
  bool isFixedIO(int x, int y) {
    return (x == 0 || x == size - 1 || y == 0 || y == size - 1);
  }
  bool isFixedIO(int xy) { return isFixedIO(xy % size, xy / size); }

  // Check if a given location exists
  bool exists(int x, int y) {
    return (x >= 0 && x < size && y >= 0 && y < size) && !(x == 0 && y == 0) &&
           !(x == 0 && y == size - 1) && !(x == size - 1 && y == 0) &&
           !(x == size - 1 && y == size - 1);
  }
  bool exists(int xy) { return exists(xy % size, xy / size); }

private:
  int size;
  std::map<std::pair<int, int>, Block *> blockMap;
};
