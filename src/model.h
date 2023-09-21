//
// Created by Aqualad Tisha on 9/21/23.
//

#ifndef OBJECT_PARSER_MODEL_H

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace objP {

enum Types { kNoType = 0, kHuman, kCar, kHouse, kTree, kAnother };

const static std::map<std::string, int> type_assert = {
    {"Человек", kHuman},  {"Машина", kCar}, {"Здание", kHouse}, {"Дерево", kTree}};

class Node {
 public:
  Node() = default;
  Node(std::string name,
       double x, double y, int type, long double time){
  name_ = std::move(name);
  x_ = x;
  y_ = y;
  type_ = type;
  time_ = time;
  };

  void Grouping() {};

  std::string name_;
  double x_ = 0;
  double y_ = 0;
  int type_ = kNoType;
  long double time_ = 0;
};

class Validator {
 public:
  Validator() = default;

  bool ValidateFile();
  static bool ValidateTokens(const std::vector<std::string> &tokens);
  std::string GetPath();

 private:
  std::string path_;
  bool status_ = true;
  std::ifstream file_;
  std::string str_;

  bool ValidatePath(const std::string &path);
};

class Parser {
 public:
  Parser() = default;
  Parser(const std::string& path, std::list<Node> &l) : list_(&l) {
    file_.open(path);
  }

  bool InitParsing();

 private:
  std::list<Node> *list_ = nullptr;
  std::ifstream file_;
  std::string str_;
};

}

#define OBJECT_PARSER_MODEL_H

#endif //OBJECT_PARSER_MODEL_H
