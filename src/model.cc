//
// Created by Aqualad Tisha on 9/21/23.
//

#include "model.h"

namespace objP {

bool Validator::ValidatePath(const std::string &path) {
  file_.open(path);

  if (!file_.is_open()) {
    return false;
  }
  return true;
}

bool Validator::ValidateFile() { //// validating right count of obj parameters
  status_ = ValidatePath(path_);
  if (status_) {

    while(!file_.eof() && status_) {
      getline(file_, str_);
      std::istringstream iss(str_);
      std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                      std::istream_iterator<std::string>());
      status_ = (tokens.size() == 5);
      if (status_) {
        status_ = ValidateTokens(tokens);
      }
    }
  }
  file_.close();
  return status_;
}
bool Validator::ValidateTokens(const std::vector<std::string> &tokens) {
  try {
    double res = std::stod(tokens[1]);
    res = std::stod(tokens[2]);
    res = std::stod(tokens[4]);

  } catch(...) {
    return false;
  }
  return true;
}
std::string Validator::GetPath() { return path_; }

bool Parser::InitParsing() {

  while(!file_.eof()) {
    getline(file_, str_);
    std::istringstream iss(str_);
    std::vector<std::string> tok((std::istream_iterator<std::string>(iss)),
                                    std::istream_iterator<std::string>());

    auto iter = type_assert.find(tok[3]);
    int type = (iter == type_assert.end()) ? 5 : iter->second;

    list_->emplace_back(tok[0], std::stod(tok[1]), std::stod(tok[2]), type, std::stod(tok[4]));
  }
  return false;
}
}
