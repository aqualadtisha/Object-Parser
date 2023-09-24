#include "front.h"

int main() {
  objP::ObjParser model;
  objP::Controller controller(model);
  objP::Front<objP::Controller> view(controller);

  view.Start();

  return 0;
}