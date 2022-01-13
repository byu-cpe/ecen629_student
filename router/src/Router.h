#ifndef ROUTER_H_
#define ROUTER_H_

class FPGA;
class Design;

class Router {
public:
  Router(bool graphics_enabled) : graphics_enabled(graphics_enabled) {}
  virtual ~Router(){};
  virtual void routeDesign(FPGA &fpga, Design &design) = 0;

protected:
  bool graphics_enabled;
};

#endif
