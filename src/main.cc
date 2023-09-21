#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> names8{"Осьминог", "Кактус", "Дуб", "Порш", "Любознатель", "Кот", "Иволга", "Собор" };
std::vector<std::string> types5{"Человек", "Машина", "Здание", "Дерево", "Другое"};

void FileGen() {
  std::ofstream file;

  std::string name;
  double x = 0;
  double y = 0;
  std::string type;
  long double times = 0;

  file.open("Objects.txt");
  srand(time(nullptr));

  for(int i = 0; i < 50; i++) {
    if (i % 5) {
      file << names8[rand() % 8] << rand() % 25 << " ";
    } else {
      file << rand() % 25 << names8[rand() % 8] << " ";
    }
    file << -100 + rand() % 201 + ((rand() % 100) / 100.0) << " ";
    file << -100 + rand() % 201 + ((rand() % 100) / 100.0) << " ";
    file << types5[rand() % 5] << " ";
    file << std::fixed << 1690000000 + rand() % 10000000 + ((rand() % 1000) / 1000.0) << "\n";
  }
  file.close();
}

int main() {
  std::string path;

  std::cout << "Hello! This program will parse your file." << std::endl;
  std::cout << "Please, enter your FULL file path: " << std::endl;
  std::cin >> path;

  std::ifstream file("/Users/aqualadt/Desktop/Git/Object-Parser/src/Objects.txt");

  while (!file.is_open()) {
    std::cout << "Invalid path or files mode parameters." << std::endl;
    std::cout << "Please, enter your FULL file path: " << std::endl;
    std::cin >> path;
    file.open("/Users/aqualadt/Desktop/Git/Object-Parser/src/Objects.txt");
  }


  file >> path;
  std::cout << path;

  // read from file
  // start program

  file.close();
  return 0;
}
