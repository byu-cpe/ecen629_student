#include <iostream>

#include "RouterSimple.h"

#include "AStarRouter.h"
#include "Design.h"
#include "Drawer.h"
#include "FPGA.h"
#include "FpgaTile.h"
#include "Net.h"
#include "RRNode.h"

static int costFcnHelper(RRNode &node, void *context);

static int costFcnHelper(RRNode &node, void *context) {
  RouterSimple *r = static_cast<RouterSimple *>(context);
  return 1;
}

void RouterSimple::routeDesign(FPGA &fpga, Design &design) {

  // This pointer to a cost function is passed into the maze router so that you
  // can use the same maze router with different routing strategies
  // (ie this simple router vs a pathfinder router)
  // In this simple router, the cost funcion always return '1' for the cost of
  // the node.
  AStarRouter mazeRouter(costFcnHelper, this);

  int i = 1;
  int numRouted = 0;
  int N = design.getNets().size();
  for (auto net : design.getNets()) {
    // if (graphics_enabled) {
    //   Drawer::draw();
    //   Drawer::loop();
    // }
    std::cout << "Routing net " << i << " of " << N;
    bool success = mazeRouter.routeNetAndCommit(*net);
    if (!success)
      std::cout << "...failed\n";
    else {
      std::cout << "\n";
      numRouted++;
    }
    i++;
  }

  std::cout << "Routed " << numRouted << " of " << N << " nets.\n";
}