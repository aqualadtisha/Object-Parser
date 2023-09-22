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

  int ParsingFile(std::string &str);
  void Grouping(int mode);

  std::list<Node> GetList();

 private:
  std::list<Node> list_;
  Validator valid_;
  Parser parse_;
  Groping group_;

  int status_ = 0;

  void Validate(std::string str);
  void Parse();
};

}


#endif //OBJECT_PARSER_FASADE_MODEL_H
