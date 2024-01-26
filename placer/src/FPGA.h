#include <map>

class Block;

class FPGA {
public:
  FPGA(int size) : size(size) {}
  ~FPGA() {}

  bool isFixedIO(int x, int y) {
    return (x == 0 || x == size - 1 || y == 0 || y == size - 1);
  }

  bool isFixedIO(int xy) { return isFixedIO(xy % size, xy / size); }

  int getSize() { return size; }

  void placeBlock(int x, int y, Block &block);
  void unplaceBlock(int x, int y);
  Block *getBlock(int x, int y);
  bool exists(int x, int y) {
    return (x >= 0 && x < size && y >= 0 && y < size) && !(x == 0 && y == 0) &&
           !(x == 0 && y == size - 1) && !(x == size - 1 && y == 0) &&
           !(x == size - 1 && y == size - 1);
  }
  bool isIO(int x, int y) {
    return (x == 0 || x == size - 1 || y == 0 || y == size - 1);
  }

private:
  int size;
  std::map<std::pair<int, int>, Block *> blockMap;
};
