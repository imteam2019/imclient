#ifndef TOOLS_H
#define TOOLS_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Tools module of the IM Toolkit.
** It supply some basic tools.
**
** Created by: Shengbo.Zeng
** Created date: 02/15/2020
**
**
**
****************************************************************************/

#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class Tools {
 public:
  Tools();
  static std::vector<std::string> *splitString(const std::string str,
                                               const char pattern);
};

#endif  // TOOLS_H
