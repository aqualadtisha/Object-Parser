#include "front.h"

int main() {
  objP::ObjParser model;
//  objP::Controller controller(model);
//  objP::Front<objP::Controller> view(controller);
//
//  view.Start();

  std::string str ="/Users/aqualadt/Desktop/Git/Object-Parser/src/tests/Obj2.txt";
  model.ParsingFile(str);
  model.Group(2, 4);

  return 0;
}