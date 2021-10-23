#ifndef ROUTER_H_
#define ROUTER_H_

class FPGA;
class Design;

class Router {
public:
  Router();
  ~Router();
  void routeDesign(FPGA &fpga, Design &design);
};

#endif
