//
// Created by Aqualad Tisha on 9/21/23.
//

#include "fasade_model.h"

namespace objP {

class Controller {
 public:
  Controller() = default;
  explicit Controller(ObjParser &m) : model_(&m){};

  int InitParse(std::string &str) {
    return model_->ParsingFile(str);
  }

  int MakeGroup(int mode) {
    model_->Grouping(mode);
    return 0;
  }


 private:
  ObjParser *model_ = nullptr;
};

}