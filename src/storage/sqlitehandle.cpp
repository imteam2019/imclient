#include "sqlitehandle.h"

SqliteHandle::SqliteHandle(std::string *dbName) { return; }

int SqliteHandle::read(list<void *> *dataList, int flag) {
  if (dataList == nullptr) {
    dataList = new list<void *>();
  }
  return 0;
}
