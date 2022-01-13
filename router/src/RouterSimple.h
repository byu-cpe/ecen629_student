#ifndef ROUTER_SRC_ROUTERSIMPLE
#define ROUTER_SRC_ROUTERSIMPLE

#include <map>

#include "Router.h"

class Net;
class Design;
class RRNode;
class FPGA;

class RouterSimple : public Router {
public:
  RouterSimple(bool enable_graphics) : Router(enable_graphics) {}
  virtual ~RouterSimple() {}

  void routeDesign(FPGA &fpga, Design &design);

private:
  void routeNet(Net &net);
};

#endif /* ROUTER_SRC_ROUTERSIMPLE */
