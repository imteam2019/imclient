#include "basicconfigure.h"

BasicConfigure::BasicConfigure() {
  init();
  return;
}

std::string BasicConfigure::getConfiglocation() const { return configlocation; }

void BasicConfigure::init() {
  char PATH[1024] = {0};
  this->appname = "IMClient";              //应用程序名称
  this->appversion = "";                   //应用程序版本号
  this->applocation = getcwd(PATH, 1024);  //应用程序位置
  this->worklocation = "/Users/shengbo.zeng/OneDrive/im";  //工作目录位置
  this->cachelocation = this->getWorklocation() + QDir::separator().toLatin1() +
                        "cache";  //缓存区目录位置
  this->datalocation = this->getWorklocation() + QDir::separator().toLatin1() +
                       "data";  //数据目录位置
  this->configlocation = this->getWorklocation() +
                         QDir::separator().toLatin1() +
                         "config";  //配置目录位置
  this->userdocmentslocation = "";  //用户文档目录
  this->appconfigurefilename = "";  //配置文件名称
  this->dbconfigurefilename = this->getConfiglocation() +
                              QDir::separator().toLatin1() +
                              "basic.json";  //数据库配置文件名称
  this->dbfilename = this->getDatalocation() + QDir::separator().toLatin1() +
                     "data.db";  //数据库文件
}
std::string BasicConfigure::getDbfilename() const { return dbfilename; }

std::string BasicConfigure::getDbconfigurefilename() const {
  return dbconfigurefilename;
}

std::string BasicConfigure::getAppconfigurefilename() const {
  return appconfigurefilename;
}

std::string BasicConfigure::getUserdocmentslocation() const {
  return userdocmentslocation;
}

std::string BasicConfigure::getDatalocation() const { return datalocation; }

std::string BasicConfigure::getCachelocation() const { return cachelocation; }

std::string BasicConfigure::getWorklocation() const { return worklocation; }

std::string BasicConfigure::getApplocation() const { return applocation; }

std::string BasicConfigure::getAppversion() const { return appversion; }

std::string BasicConfigure::getAppname() const { return appname; }
