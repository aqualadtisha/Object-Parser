//
// Created by Aqualad Tisha on 9/21/23.
//

#include "fasade_model.h"

namespace objP {

std::list<Node> ObjParser::GetList() { return list_; }

void ObjParser::Parse()  {
  std::string path = valid_.GetPath();
  parse_ = Parser(path, list_);
  parse_.InitParsing();
}

void ObjParser::Validate(std::string str)  {
  valid_ = Validator();
  valid_.SetPath(str);
  status_ = valid_.ValidateFile();
}

int ObjParser::ParsingFile(std::string &str)  {
  Validate(str);
  if (status_ == kOk) Parse();
  return status_;
}

void ObjParser::Grouping(int mode) {
  group_ = Groping(list_);
  group_.SwitchMode(mode);
}

}
