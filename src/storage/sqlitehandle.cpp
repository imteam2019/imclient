#include "sqlitehandle.h"

SqliteHandle::SqliteHandle() {
  this->dbc = Configure::getDBConfig();

  db = QSqlDatabase::addDatabase("QSQLITE");
  this->db.setDatabaseName(Configure::getBasicConfig()->getDbfilename().data());
  //打开连接
  if (!db.open()) {
    qDebug() << endl << db.lastError();
    qFatal("Failed to connect.");
  }

  qDebug("Connected!");

  this->qry = new QSqlQuery(this->db);
  this->exec(this->dbc->getSQL("1001", "101"), nullptr,
             new list<map<std::string, std::string> *>);
  return;
}

SqliteHandle::~SqliteHandle() {
  if (this->db.isOpen()) this->db.close();
  if (this->dbc != nullptr) delete this->dbc;
  if (this->qry != nullptr) delete this->qry;
}

/**
 * @brief SqliteHandle::exec 根据给定的sql语句，绑定参数，并执行返回
 * @param sql 戴执行的sql语句
 * @param values  参数值
 * @param results
 * 存放执行select操作后返回的数据集，非select操作该值默认为nullptr
 * @return 成功：返回影响到的数据集记录数量，失败：-1
 */
int SqliteHandle::exec(std::string sql, vector<std::string> *values,
                       list<map<std::string, std::string> *> *results) {
  if (sql.empty()) return -1;

  // 检查sql中是否有占位符，如果有，则占位符数量应该等于条件值的数量,否则返回-1
  std::string strOper;
  size_t pos = 0, numbers = 0;
  while (pos <= sql.length()) {
    pos = sql.find('?', pos);
    if (pos <= sql.length()) {
      numbers++, pos++;
    }
  }

  if (numbers > 0 && values == nullptr) return -1;
  if (numbers > 0 && numbers != values->capacity()) return -1;

  // 获取sql的操作符，判断是select,delete,update or insert的何种操作
  // 如果是select操作，则results参数不能为nullptr
  strOper = sql.substr(0, sql.find(' '));
  if (strOper.empty()) return -1;
  std::transform(strOper.begin(), strOper.end(), strOper.begin(), ::toupper);
  if (strOper == "SELECT" && results == nullptr) return -1;

  // 开始执行db处理
  this->qry->prepare(QString::fromStdString(sql));

  // 条件处理
  if (values != nullptr && values->capacity() > 0) {
    for (vector<std::string>::iterator i = values->begin(); i != values->end();
         i++) {
      this->qry->addBindValue(i->data());
    }
  }

  if (this->qry->exec() && strOper == "SELECT") {
    QSqlRecord r;
    map<std::string, std::string> *tr;
    while (this->qry->next()) {
      r = this->qry->record();
      tr = new map<std::string, std::string>;
      for (int i = 0; i < r.count(); i++) {
        tr->insert(std::pair<std::string, std::string>(
            r.fieldName(i).toStdString(), r.value(i).toString().toStdString()));
      }
      results->push_back(tr);
    };
  }

  return this->qry->numRowsAffected();
}
