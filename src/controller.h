//
// Created by Aqualad Tisha on 9/21/23.
//

#include "fasade_model.h"

namespace objP {
class Controller {
 public:
  Controller() = default;
  explicit Controller(ObjParser &m) : model_(&m){};

  bool InitParse() {
    model_->ParsingFile();
    return 0;
  }

  bool MakeGroup(int mode) {
    model_->Grouping();
    return 0;
  }


 private:
  ObjParser *model_;
};
}