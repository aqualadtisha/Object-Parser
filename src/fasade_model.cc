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

void ObjParser::Validate()  {
  valid_ = Validator();
  status_ = valid_.ValidateFile();
}

void ObjParser::ParsingFile()  {
  Validate();
  if (status_) Parse();
}

}
