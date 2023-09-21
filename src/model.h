//
// Created by Aqualad Tisha on 9/21/23.
//

#ifndef OBJECT_PARSER_MODEL_H

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

namespace objP {

enum Types { kNoType = 0, kHuman, kCar, kHouse, kTree, kAnother };

const static std::map<std::string, int> type_assert = {
    {"Человек", kHuman},  {"Машина", kCar}, {"Здание", kHouse}, {"Дерево", kTree}};

class Node {
 public:
  Node() = default;
  Node(int i){

  };

  std::string name;
  double x = 0;
  double y = 0;
  int type = kNoType;
  long double time = 0;
};

class Validator {
 public:
  Validator() = default;
  Validator(std::string str) {

  }

  void ValidatePath() {
    std::cout << "Hello! This program will parse your file." << std::endl;
    std::cout << "Please, enter your FULL file path: " << std::endl;
    std::cin >> path_;

    std::ifstream file(
        "/Users/aqualadt/Desktop/Git/Object-Parser/src/Objects.txt");

    while (!file.is_open()) {
      std::cout << "Invalid path or files mode parameters." << std::endl;
      std::cout << "Please, enter your FULL file path: " << std::endl;
      std::cin >> path_;
      file.open("/Users/aqualadt/Desktop/Git/Object-Parser/src/Objects.txt");
    }
  }

 private:
  std::string path_;
};

class Parser {
 public:
  Parser() = default;
  Parser(std::string str) {

  }

 private:
  std::list<Node> *list_ = nullptr;

};

class Operations {
  void RangeSort() {};
};

}

#define OBJECT_PARSER_MODEL_H

#endif //OBJECT_PARSER_MODEL_H
