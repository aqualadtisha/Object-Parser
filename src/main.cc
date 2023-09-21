#include <fstream>
#include <iostream>
#include <vector>
#include "controller.h"

namespace objP {
  std::vector<std::string> names8{"Осьминог",    "Кактус", "Дуб",    "Порш",
                                  "Любознатель", "Кот",    "Иволга", "Собор"};
  std::vector<std::string> types5{"Человек", "Машина", "Здание", "Дерево",
                                  "Другое"};

  void FileGen() {
    std::ofstream file;

    std::string name;
    double x = 0;
    double y = 0;
    std::string type;
    long double times = 0;

    file.open("Objects.txt");
    srand(time(nullptr));

    for (int i = 0; i < 50; i++) {
      if (i % 5) {
        file << names8[rand() % 8] << rand() % 25 << " ";
      } else {
        file << rand() % 25 << names8[rand() % 8] << " ";
      }
      file << -100 + rand() % 201 + ((rand() % 100) / 100.0) << " ";
      file << -100 + rand() % 201 + ((rand() % 100) / 100.0) << " ";
      file << types5[rand() % 5] << " ";
      file << std::fixed
           << 1690000000 + rand() % 10000000 + ((rand() % 1000) / 1000.0)
           << "\n";
    }
    file.close();
  }

int main() {
  ObjParser model;
  Controller controll(model);
  std::string path;

  std::cout << "Hello! This program will parse your file." << std::endl;
  std::cout << "Please, enter your FULL file path: " << std::endl;
  std::cin >> path;


//      std::cout << "Invalid path or files mode parameters." << std::endl;
//      std::cout << "Please, enter your FULL file path or quit program with \"Q\": " << std::endl;
//      std::cin >> path;
//      if (path == "Q")


  controll.InitParse();

  std::cout << "Grouping by distance: -- 1" << std::endl;
  std::cout << "Grouping by name:     -- 2" << std::endl;
  std::cout << "Grouping by time:     -- 3" << std::endl;
  std::cout << "Grouping by type:     -- 4" << std::endl;

  int mode = 0;
  std::cin >> mode;

  controll.MakeGroup(mode);

  std::cout << "Check results in file \"Results.txt\" in Project folder." << std::endl;

  return 0;
}
}