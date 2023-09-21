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

  void ParsingFile();
  void Grouping();

  std::list<Node> GetList();

 private:
  std::list<Node> list_;
  Validator valid_;
  Parser parse_;

  bool status_ = true;
  int mode = 0;

  void Validate();
  void Parse();
};

}


#endif //OBJECT_PARSER_FASADE_MODEL_H
