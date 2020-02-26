#ifndef BAICCONFIGURE_H
#define BAICCONFIGURE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Common Confiture module of the IM Toolkit.
** It's used to for application config info.
**
** Created by: Shengbo.Zeng
** Created date: 02/25/2020
**
**
**
****************************************************************************/
#include <QDebug>
#include <QDir>
#include <iostream>

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif
class BasicConfigure {
  friend class Configure;

 public:
  std::string getAppname() const;

  std::string getAppversion() const;

  std::string getApplocation() const;

  std::string getWorklocation() const;

  std::string getCachelocation() const;

  std::string getDatalocation() const;

  std::string getUserdocmentslocation() const;

  std::string getAppconfigurefilename() const;

  std::string getDbconfigurefilename() const;

  std::string getDbfilename() const;

  std::string getConfiglocation() const;

 protected:
  BasicConfigure();

 private:
  std::string appname = "";      //应用程序名称
  std::string appversion = "";   //应用程序版本号
  std::string applocation = "";  //应用程序位置
  std::string worklocation = "/Users/shengbo.zeng/OneDrive/im";  //工作目录位置
  std::string cachelocation = "";         //缓存区目录位置
  std::string datalocation = "";          //数据目录位置
  std::string configlocation = "";        //配置文件目录
  std::string userdocmentslocation = "";  //用户文档目录
  std::string appconfigurefilename = "";  //配置文件名称
  std::string dbconfigurefilename = "";   //数据库配置文件名称
  std::string dbfilename = "";            //数据库文件

 private:
  void init();
};

#endif  // BAICCONFIGURE_H
