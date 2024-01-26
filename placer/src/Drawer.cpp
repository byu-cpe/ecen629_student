#include "Drawer.h"

#include <cassert>
#include <string>

#include "Block.h"
#include "Design.h"
#include "Net.h"
#include "easygl/graphics.h"

Design *Drawer::design = nullptr;

static bool show_nets = false;

void draw_hide_rats_nest(void (*drawscreen)())
{
  if (!show_nets)
    change_button_text("Show Nets", "Hide Nets");
  else
    change_button_text("Hide Nets", "Show Nets");
  show_nets = !show_nets;
  drawscreen();
}

Drawer::Drawer()
{
  // TODO Auto-generated constructor stub
}

Drawer::~Drawer()
{
  // TODO Auto-generated destructor stub
}

void Drawer::init()
{
  // TODO Auto-generated constructor stub

  init_graphics("Some Example Graphics", WHITE);

  // Set-up drawing coordinates. We choose from (xl,ybottom) = (0,0) to
  // (xr,ytop) = (1000,1000)
  //	int totalWidth = fpga->getN() * getTileWidth(fpga->getW());
  init_world(0., 0., Design::FPGA_SIZE + 2 * OUTSIDE_PAD,
             Design::FPGA_SIZE + 2 * OUTSIDE_PAD);

  create_button("Window", "Show Nets", draw_hide_rats_nest);

  // This message will show up at the bottom of the window.
  update_message("Interactive graphics example.");
}

void Drawer::draw()
{

  clearscreen();
  drawrect(OUTSIDE_PAD, OUTSIDE_PAD, Design::FPGA_SIZE + OUTSIDE_PAD,
           Design::FPGA_SIZE + OUTSIDE_PAD);

  // Draw blocks
  for (auto b : design->getBlocks())
  {
    if (b->isImaginary())
      continue;
    drawBlock(b);
  }

  // Draw nets
  for (auto n : design->getNets())
  {
    bool imag = false;
    for (auto b : n->getBlocks())
      if (b->isImaginary())
        imag = true;
    if (!imag && show_nets)
    {
      drawNet(n);
    }
  }
}

void Drawer::drawBlock(Block *b)
{
  if (b->isFixed())
  {
    fillrect(b->getX() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getY() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getX() + BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getY() + BLOCK_SIZE / 2 + OUTSIDE_PAD);
  }
  else
  {
    drawrect(b->getX() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getY() - BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getX() + BLOCK_SIZE / 2 + OUTSIDE_PAD,
             b->getY() + BLOCK_SIZE / 2 + OUTSIDE_PAD);
    drawtext(b->getX() + OUTSIDE_PAD, b->getY() + OUTSIDE_PAD,
             std::to_string(b->getIdx()).c_str(), 100);
  }
}

void Drawer::drawNet(Net *net)
{
  // Pick a source that isn't a pad
  Block *source = nullptr;
  Block *first = nullptr;
  for (auto b : net->getBlocks())
  {
    if (!b->isFixed())
    {
      source = b;
      break;
    }
    if (first == nullptr)
      first = b;
  }
  if (!source)
    source = first;
  assert(source);

  for (auto b : net->getBlocks())
  {
    if (source == b)
      continue;
    drawline(b->getX() + OUTSIDE_PAD, b->getY() + OUTSIDE_PAD,
             source->getX() + OUTSIDE_PAD, source->getY() + OUTSIDE_PAD);
  }
}

void nothing(float x, float y) {}

void Drawer::loop() { event_loop(nothing, NULL, nullptr, &(Drawer::draw)); }

void Drawer::close() { close_graphics(); }
