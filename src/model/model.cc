#include "model.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <valarray>
namespace objP {

static double FindDistanse(const Node &a) {
  return std::sqrt(std::pow(a.x_, 2) + std::pow(a.y_, 2));
}

std::string Node::NodeToString() const {
  return name_ + " " + std::to_string(x_) + " " + std::to_string(y_) + " " +
         type_ + " " + std::to_string(time_);
}

int Validator::ValidatePath() {
  if (path_ == "Q") return kQuit;

  file_.open(path_);

  if (!file_.is_open()) {
    return kValidPath;
  }
  return kOk;
}

int Validator::ValidateFile() {  //// validating right count of obj parameters
  status_ = ValidatePath();
  if (status_ == kOk) {
    while (!file_.eof() && !status_) {
      getline(file_, str_);
      std::istringstream iss(str_);
      std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                      std::istream_iterator<std::string>());
      if (tokens.empty()) continue;
      status_ = (tokens.size() == 5) ? kOk : kValidFile;
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
    res += std::stod(tokens[2]);
    res += std::stod(tokens[4]);

  } catch (...) {
    return kValidFile;
  }
  return kOk;
}
std::string Validator::GetPath() { return path_; }

void Validator::SetPath(std::string &p) { path_ = std::move(p); }

bool Parser::InitParsing() {
  while (!file_.eof()) {
    getline(file_, str_);
    std::istringstream iss(str_);
    std::vector<std::string> tok((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());

    if (!tok.empty())
      list_->emplace_back(tok[0], std::stod(tok[1]), std::stod(tok[2]), tok[3],
                          std::stod(tok[4]));
  }
  return false;
}

int Grouping::SwitchMode(int mode, int n) {
  switch (mode) {
    case 1:
      GroupByDistance();
      break;
    case 2:
      GroupByName();
      break;
    case 3:
      GroupByTime();
      break;
    case 4:
      GroupByType(n);
      break;
    default:
      return kGroup;
  }
  return kOk;
}

void Grouping::GroupByDistance() {
  list_->sort(CompareCoords);

  GroupByDistWrite();
}

void Grouping::GroupByName() {
  list_->sort(CompareNames);

  GroupByNameWrite();
}

bool Grouping::CheckRusLetter(int c) { return c <= -48 && c >= -81; }

void Grouping::GroupByTime() {
  list_->sort(CompareTime);

  GroupByTimeWrite();
}

void Grouping::GroupByType(int n) {
  list_->sort(CompareType);

  std::vector<std::string> types{};

  WriteTypesToVector(types, n);

  GroupByTypeWrite(types);
}

void Grouping::WriteTypesToVector(std::vector<std::string> &types, int n) {
  int count = 0;
  std::string tmp = list_->front().type_;

  for (const Node &node : *list_) {
    if (node.type_ == tmp) {
      count++;
    } else {
      if (count >= n) {
        types.push_back(tmp);
      }
      count = 1;
      tmp = node.type_;
    }
  }

  if (count >= n) {
    types.push_back(tmp);
  }
}

int Grouping::CompareNames(const Node &a, const Node &b) {
  return (a.name_ < b.name_);
}
int Grouping::CompareCoords(const Node &a, const Node &b) {
  return (FindDistanse(a) < FindDistanse(b));
}
int Grouping::CompareTime(const Node &a, const Node &b) {
  return (a.time_ < b.time_);
}

int Grouping::CompareType(const Node &a, const Node &b) {
  return (a.type_ < b.type_);
}
void Grouping::GroupByTypeWrite(std::vector<std::string> &types) {
  file.open("Results.txt");

  WriteTypesFromList(types);

  if (!list_->empty()) {
    file << "\nGroup "
         << "Разное:\n"
         << std::endl;
    for (const Node &node : *list_) {
      file << node.NodeToString() << std::endl;
    }
  }
  file.close();
}

void Grouping::WriteTypesFromList(std::vector<std::string> &types) {
  size_t count = 0;
  bool flag = false;

  file << "\nGroup " << types[0] << ":\n" << std::endl;

  auto iter = list_->begin();
  while (iter != list_->end()) {
    if (iter->type_ == types[count]) {
      file << iter->NodeToString() << std::endl;
      --iter;
      list_->erase(++iter);
      iter++;
      flag = true;
    } else if (flag) {
      count++;
      if (count < types.size()) {
        file << "\nGroup " << types[count] << ":\n" << std::endl;
      }
      flag = false;
    } else {
      iter++;
    }
  }
}

void Grouping::GroupByTimeWrite() {
  file.open("Results.txt");

  time_t result = time(nullptr);
  std::string now, time;
  now = ctime(&result);

  std::istringstream iss(now);
  std::vector<std::string> t_now((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());

  std::vector<std::string> interval{"Сегодня:\n",          "Вчера:\n",
                                    "В течение недели:\n", "В этом месяце:\n",
                                    "В этом году:\n",      "Ранее:\n"};

  int state = -1, count = -1;

  for (const Node &node : *list_) {
    time_t milisec = node.time_;
    time = ctime(&milisec);
    std::istringstream iss2(time);
    std::vector<std::string> t_node((std::istream_iterator<std::string>(iss2)),
                                    std::istream_iterator<std::string>());

    count = CheckTimeInterval(t_now, t_node);

    if (state != count) {
      state = count;
      file << "\nGroup " << interval[state] << std::endl;
    }

    file << node.NodeToString() << std::endl;
  }
  file.close();
}

int Grouping::CheckTimeInterval(std::vector<std::string> &now,
                                std::vector<std::string> &node) {
  int count = 0;
  if (node[4] == now[4]) {
    if (node[1] == now[1]) {
      if (node[2] == now[2]) {
        count = 0;
      } else {
        long sub = std::stol(now[2]) - std::stoi(node[2]);
        if (sub > 7) {
          count = 3;
        } else {
          count = (sub == 1) ? 1 : 2;
        }
      }
    } else {
      count = 4;
    }
  } else {
    count = 5;
  }
  return count;
}

void Grouping::GroupByDistWrite() {
  file.open("Results.txt");

  std::vector<std::string> distanses{
      "Group До 100 единиц:\n", "Group До 1000 единиц:\n",
      "Group До 10000 единиц:\n", "Слишком далеко"};

  double dist = FindDistanse(list_->front());

  int count = CheckDistanse(dist);
  file << distanses[count] << std::endl;

  for (const Node &node : *list_) {
    dist = FindDistanse(node);
    if (dist > 100 * std::pow(10, count) && count != 3) {
      count++;
      file << '\n' << distanses[count] << std::endl;
    }
    file << node.NodeToString() << std::endl;
  }
  file.close();
}

int Grouping::CheckDistanse(double dist) {
  int count = -1;
  if (dist < 100) {
    count = 0;
  } else if (dist < 1000) {
    count++;
  } else if (dist < 10000) {
    count += 2;
  } else {
    count += 3;
  }
  return count;
}
void Grouping::GroupByNameWrite() {
  QFile qfile("Results.txt");
  qfile.open(QIODevice::WriteOnly);
  QTextStream out(&qfile);

  QString letter = QString::fromStdString(list_->front().name_);
  QString name{};

  if (!CheckRusLetter(list_->front().name_[0])) {
    letter = '#';
  }
  out << "Group " << letter[0] << ":\n\n";

  for (const Node &node : *list_) {
    name = QString::fromStdString(node.name_);

    if (name[0] != letter[0] && CheckRusLetter(name.toStdString().at(0))) {
      letter = name;
      out << "\nGroup " << letter[0] << ":\n\n";
    }
    out << QString::fromStdString(node.NodeToString()) << '\n';
  }
  qfile.close();
}

}  // namespace objP