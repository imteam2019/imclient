#include "common.h"

Tools::Tools() {}

std::vector<std::string> *Tools::splitString(const std::string str,
                                             const char pattern) {
  vector<std::string> *res = new vector<std::string>;
  std::stringstream input(str);  //读取str到字符串流中
  string temp;
  //使用getline函数从字符串流中读取,遇到分隔符时停止,和从cin中读取类似
  //注:getline默认是可以读取空格的
  while (getline(input, temp, pattern)) {
    res->push_back(temp);
  }
  return res;
}
