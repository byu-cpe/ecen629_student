#ifndef ROUTER_H_
#define ROUTER_H_

class FPGA;
class Design;

class Router {
public:
  Router(){};
  virtual ~Router(){};
  virtual void routeDesign(FPGA &fpga, Design &design) = 0;
};

#endif
