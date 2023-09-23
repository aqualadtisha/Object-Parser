#ifndef OBJECT_PARSER_FRONT_H
#define OBJECT_PARSER_FRONT_H

#include "controller.h"

namespace objP {

template <class Controller = objP::Controller>
class Front {
 public:
  Front() = default;
  explicit Front(Controller &c) : controll_(&c){};
  ~Front() = default;

  void Start();

 private:
  Controller *controll_ = nullptr;
  bool quit_ = false;

  void SetPath();
};

template <class Controller>
void Front<Controller>::Start() {
  std::cout << "Hello! This program will parse your file." << std::endl;
  SetPath();
  if (!quit_) {
    std::cout << "Please, switch grouping mode:" << std::endl;
    std::cout << "Grouping by distance: -- 1" << std::endl;
    std::cout << "Grouping by name:     -- 2" << std::endl;
    std::cout << "Grouping by time:     -- 3" << std::endl;
    std::cout << "Grouping by type:     -- 4" << std::endl;

    int mode = 0, n = 0;
    std::cin >> mode;

    if (mode == 4) {
      std::cout << "Please, enter the min group size:" << std::endl;
      std::cin >> n;
    }

    controll_->MakeGroup(mode, n);

    std::cout << "Check results in file \"Results.txt\" in Project folder."
              << std::endl;
  }
  std::cout << "Bye!" << std::endl;
}

template <class Controller>
void Front<Controller>::SetPath() {
  std::string path;
  bool error = true;
  std::cout << "Please, enter your FULL file path or \"Q\" to quit: "
            << std::endl;

  while (error && !quit_) {
    std::cin >> path;
    int res = controll_->InitParse(path);

    if (res == kOk) {
      error = false;
    } else if (res == kQuit) {
      quit_ = true;
    } else {
      if (res == kValidFile) {
        std::cout << "Invalid file." << std::endl;
      } else {
        std::cout << "Invalid path parameters." << std::endl;
      }
      std::cout << "Please, try again." << std::endl;
    }
  }
}

}  // namespace objP

#endif  // OBJECT_PARSER_FRONT_H
