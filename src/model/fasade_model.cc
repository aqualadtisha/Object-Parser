#include "fasade_model.h"

namespace objP {

void ObjParser::Parse() {
  std::string path = valid_.GetPath();
  parse_ = Parser(path, list_);
  parse_.InitParsing();
}

void ObjParser::Validate(std::string str) {
  valid_ = Validator();
  valid_.SetPath(str);
  status_ = valid_.ValidateFile();
}

int ObjParser::ParsingFile(std::string &str) {
  Validate(str);
  if (status_ == kOk) Parse();
  return status_;
}

void ObjParser::Group(int mode, int n) {
  group_ = Grouping(list_);
  group_.SwitchMode(mode, n);
}

}  // namespace objP
