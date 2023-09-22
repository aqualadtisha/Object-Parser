#include "front.h"


int main() {
  objP::ObjParser model;
  objP::Controller controller(model);
  objP::Front view(controller);

  view.Start();

  return 0;
}