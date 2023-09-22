//
// Created by Aqualad Tisha on 9/21/23.
//

#include "model.h"

#include <valarray>

namespace objP {

void Node::NodeToString(std::string &str) {
  str = name_ + std::to_string(x_) + std::to_string(y_) + type_ + std::to_string(time_);
}

int Validator::ValidatePath() {
  if (path_ == "Q") return kQuit;

  file_.open(path_);

  if (!file_.is_open()) {
    return kValidPath;
  }
  return kOk;
}

int Validator::ValidateFile() { //// validating right count of obj parameters
  status_ = ValidatePath();
  if (status_ == kOk) {

    while(!file_.eof() && status_) {
      getline(file_, str_);
      std::istringstream iss(str_);
      std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                      std::istream_iterator<std::string>());
      status_ = (tokens.size() == 5);
      if (status_ == kOk) {
        status_ = ValidateTokens(tokens);
      }
    }
  }
  file_.close();
  return status_;
}
int Validator::ValidateTokens(const std::vector<std::string> &tokens) {
  try {
    double res = std::stod(tokens[1]);
    res = std::stod(tokens[2]);
    res = std::stod(tokens[4]);

  } catch(...) {
    return kValidFile;
  }
  return kOk;
}
std::string Validator::GetPath() { return path_; }

void Validator::SetPath(std::string &p) { path_ = std::move(p); }

bool Parser::InitParsing() {
  while(!file_.eof()) {
    getline(file_, str_);
    std::istringstream iss(str_);
    std::vector<std::string> tok((std::istream_iterator<std::string>(iss)),
                                    std::istream_iterator<std::string>());

    if (!tok.empty()) list_->emplace_back(tok[0], std::stod(tok[1]), std::stod(tok[2]), tok[3], std::stod(tok[4]));
  }
  return false;
}

int Grouping::SwitchMode(int mode) {
  switch(mode){
    case 1: GroupByDistance(); break;
    case 2: GroupByName(); break;
    case 3: GroupByTime(); break;
    case 4: GroupByType(); break;
    default: return kGroup;
  }
  return kOk;
}

void Grouping::GroupByDistance() {
  std::qsort(&list_, list_.size(), sizeof(Node),CompareCoords);
}

void Grouping::GroupByName() {
  std::qsort(&list_, sizeof(Node), list_.size(),CompareNames);
  std::ofstream file;
  file.open("../Results.txt");
  for (const Node& node : list_) {
    std::cout << node.name_ << std::endl;
  }
}

void Grouping::GroupByTime() {
  std::qsort(&list_, list_.size(), sizeof(Node),CompareTime);
}

void Grouping::GroupByType() {
  std::qsort(&list_, list_.size(), sizeof(Node),CompareType);
}

int Grouping::CompareNames(const void *a, const void *b) {

  const Node *l_ = (Node*) a;
  const Node *r_ = (Node*) b;

  if (l_->name_[0] > r_->name_[0])
    return 1;
  else if (l_->name_[0] < r_->name_[0])
    return -1;
  return 0;
}
int Grouping::CompareCoords(const void *a, const void *b) {

  const Node *l_ = (Node*) a;
  const Node *r_ = (Node*) b;

  double distanse_a = std::sqrt(std::pow(l_->x_, 2) + std::pow(l_->y_, 2));
  double distanse_b = std::sqrt(std::pow(r_->x_, 2) + std::pow(r_->y_, 2));

  if (distanse_a > distanse_b)
    return 1;
  else if (distanse_a < distanse_b)
    return -1;
  return 0;
}
int Grouping::CompareTime(const void *a, const void *b) {

  const Node *l_ = (Node*) a;
  const Node *r_ = (Node*) b;

  if (l_->time_ > r_->time_)
    return 1;
  else if (l_->time_ < r_->time_)
    return -1;
  return 0;
}

int Grouping::CompareType(const void *a, const void *b) {

  const Node *l_ = (Node*) a;
  const Node *r_ = (Node*) b;

  if (l_->type_ > r_->type_)
    return 1;
  else if (l_->type_ < r_->type_)
    return -1;

  return 0;
}

}
