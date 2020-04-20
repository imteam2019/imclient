

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <cstdio>
#include <cstdlib>

#include "boost/any.hpp"
#include "boost/unordered_map.hpp"
#include "common/encrypt.h"
#include "configure/configure.h"
#include "configure/dbconfigure.h"
#include "login/signin.h"
#include "login/signup.h"
#include "mainwindow.h"
#include "message/data.h"
#include "message/message.h"
#include "network/tcpconn.h"
#include "storage/sqlitehandle.h"
#include "ui/loginform.h"

int main(int argc, char *argv[]) {
  // SqliteHandle *sh = new SqliteHandle();

  QApplication a(argc, argv);
  MainWindow w;
  Configure *config = new Configure();
  config->getBasicConfig()->getDbfilename();
  w.show();
  return a.exec();
}
