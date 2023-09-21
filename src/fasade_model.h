//
// Created by Aqualad Tisha on 9/21/23.
//

#ifndef OBJECT_PARSER_FASADE_MODEL_H
#define OBJECT_PARSER_FASADE_MODEL_H

#include "model.h"

namespace objP {

class ObjParser {
 public:
  ObjParser() = default;
  ObjParser(const ObjParser& other) = delete;
  ObjParser(ObjParser&& other) = delete;
  void operator=(const ObjParser& other) = delete;
  ~ObjParser() = default;

  int ParsingFile() {

  }

  int Validate(std::string str) {
    valid_ = Validator();
  }

  int Parse(std::string str) {
    parse_ = Parser();
  }

  int Operations() {
    opers_ = Operations();
  }

 private:
  std::list<Node> list_;
  Validator valid_;
  Parser parse_;
  Operations opers_;
};

}


#endif //OBJECT_PARSER_FASADE_MODEL_H
