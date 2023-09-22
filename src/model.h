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
enum Errors { kOk = 0, kValidPath, kValidFile, kPars, kGroup, kQuit };

const static std::map<std::string, int> type_assert = {
    {"Человек", kHuman},  {"Машина", kCar}, {"Здание", kHouse}, {"Дерево", kTree}};

class Node {
 public:
  Node() = default;
  Node(std::string name,
       double x, double y, std::string type, long double time) {
  name_ = std::move(name);
  x_ = x;
  y_ = y;
  type_ = type;
  time_ = time;
  };

  void NodeToString(std::string &str);

  std::string name_;
  double x_ = 0;
  double y_ = 0;
  std::string type_;
  long double time_ = 0;
};

class Validator {
 public:
  Validator() = default;

  int ValidateFile();
  static int ValidateTokens(const std::vector<std::string> &tokens);
  std::string GetPath();
  void SetPath(std::string &p);

 private:
  std::string path_;
  int status_ = kOk;
  std::ifstream file_;
  std::string str_;

  int ValidatePath();
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

class Grouping{
 public:
  Grouping() = default;
  explicit Grouping(std::list<Node> &l) : list_(l){};

  int SwitchMode(int mode);
  void GroupByDistance();
  void GroupByName();
  void GroupByTime();
  void GroupByType();

 private:
  std::list<Node> list_;

  static int CompareNames(const void *a, const void *b);
  static int CompareCoords(const void *a, const void *b);
  static int CompareTime(const void *a, const void *b);
  static int CompareType(const void *a, const void *b);
};

}

#define OBJECT_PARSER_MODEL_H

#endif //OBJECT_PARSER_MODEL_H
