#include <fstream>
#include <iostream>
#include <vector>

namespace objP {

std::vector<std::string> names8{"Осьминог", "Кактус", "Дуб", "Порш", "Любознатель", "Кот", "Иволга", "Собор"};
std::vector<std::string> types5{"Человек", "Машина", "Здание", "Дерево", "Другое"};

void FileGen() {
  std::ofstream file;

  long now = time(nullptr);

  file.open("../Obj2.txt");
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
    file << ((1690000000 + rand() % 10000000) % now)
         << "\n";
  }
  file.close();
}

}

int main() {
  objP::FileGen(); /// function for generate test files
  return 0;
}