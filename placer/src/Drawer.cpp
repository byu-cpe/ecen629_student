#include "Drawer.h"

#include <cassert>
#include <string>

#include "Block.h"
#include "Design.h"
#include "Net.h"
#include "easygl/graphics.h"

static bool show_nets = true;
Design *Drawer::design = nullptr;

void Drawer::setDesign(Design &new_design) { Drawer::design = &new_design; }

void draw_hide_rats_nest(void (*drawscreen)()) {
  if (!show_nets)
    change_button_text("Show Nets", "Hide Nets");
  else
    change_button_text("Hide Nets", "Show Nets");
  show_nets = !show_nets;
  drawscreen();
}

void Drawer::init() {
  // TODO Auto-generated constructor stub
  // TODO Auto-generated constructor stub

  init_graphics("Some Example Graphics", WHITE);

  // Set-up drawing coordinates. We choose from (xl,ybottom) = (0,0) to
  // (xr,ytop) = (1000,1000)
  //	int totalWidth = fpga->getN() * getTileWidth(fpga->getW());
  init_world(0., 0.,
             design->getDevice().getSize() * (BLOCK_PAD + BLOCK_SIZE) +
                 2 * OUTSIDE_PAD,
             design->getDevice().getSize() * (BLOCK_PAD + BLOCK_SIZE) +
                 2 * OUTSIDE_PAD);

  create_button("Window", "Hide Nets", draw_hide_rats_nest);

  // This message will show up at the bottom of the window.
  update_message("Interactive graphics example.");
}

// Drawer::~Drawer() {
//   // TODO Auto-generated destructor stub
// }

// Get drawing pixel position for a x or y position
int Drawer::getXY(int xy_pos) {
  return OUTSIDE_PAD + xy_pos * (BLOCK_SIZE + BLOCK_PAD);
}

void Drawer::draw() {
  clearscreen();
  int size = design->getDevice().getSize();
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (!design->getDevice().exists(x, y))
        continue;
      if (design->getDevice().isFixedIO(x, y)) {
        setcolor(LIGHTGREY);
        fillrect(getXY(x), getXY(y), getXY(x) + BLOCK_SIZE,
                 getXY(y) + BLOCK_SIZE);
      }
      setcolor(BLACK);
      drawrect(getXY(x), getXY(y), getXY(x) + BLOCK_SIZE,
               getXY(y) + BLOCK_SIZE);
      // Check if block is here
      Block *b = design->getDevice().getBlock(x, y);
      if (b) {
        drawtext(getXY(x) + BLOCK_SIZE / 2, getXY(y) + BLOCK_SIZE / 2,
                 std::to_string(b->getIdx()).c_str(), BLOCK_SIZE);
      }
    }
    // Draw blocks
    // for (auto &b : design.getBlocks()) {
    //  // // Draw blocks
    // for (auto &b : design.getBlocks()) {
    // drawBlock(b);
  }

  // // Draw nets
  for (auto n : design->getNets()) {
    for (auto b : n->getBlocks())
      if (show_nets) {
        drawNet(*n);
        //   if (b->isFixed()) {
        //     fillrect(b->getX() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
        //              b->getY() + BLOCK_SIZE / 2 + OUTSIDE_PAD);
        //   } else {
        //     drawrect(b->getX() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
        //              b->getY() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
        //              b->getX() + BLOCK_SIZE / 2 + OUTSIDE_PAD,
        //              b->getY() + BLOCK_SIZE / 2 + OUTSIDE_PAD);
        //     drawtext(b->getX() + OUTSIDE_PAD, b->getY() + OUTSIDE_PAD,
        //              std::to_string(b->getIdx()).c_str(), 100);
        //   }
        //   drawtext(b->getX() + OUTSIDE_PAD, b->getY() + OUTSIDE_PAD,
        //            std::to_string(b->getIdx()).c_str(), 100);
        // }
      }
  }
}

void Drawer::drawNet(Net &net) {
  Block *source = net.getBlocks()[0];
  for (auto b : net.getBlocks()) {
    if (b == source)
      continue;
    drawline(getXY(b->getX()) + BLOCK_SIZE / 2,
             getXY(b->getY()) + BLOCK_SIZE / 2,
             getXY(source->getX()) + BLOCK_SIZE / 2,
             getXY(source->getY()) + BLOCK_SIZE / 2);
  }
}

void nothing(float x, float y) {}

void Drawer::loop() { event_loop(nothing, NULL, nullptr, &(Drawer::draw)); }

void Drawer::close() { close_graphics(); }
