#include "model/facade_model.h"

namespace objP {

class Controller {
 public:
  Controller() = default;
  explicit Controller(ObjParser &m) : model_(&m){};

  int InitParse(std::string &str) { return model_->ParsingFile(str); }

  int MakeGroup(int mode, int n) {
    model_->Group(mode, n);
    return 0;
  }

 private:
  ObjParser *model_ = nullptr;
};

}  // namespace objP