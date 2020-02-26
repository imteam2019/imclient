#include "dbconfigure.h"

DBConfigure::DBConfigure(std::string dbconfigfile) {
  QDir dir;

  if (dir.exists(QString::fromStdString(dbconfigfile))) {
    this->dbconfigfile = dbconfigfile;
    this->init();
  }
  return;
}

/**
 * @brief Configure::~Configure
 *  删除Sql模版中的所有字符串对象
 */
DBConfigure::~DBConfigure() {
  delete this->dbDoc;
  delete this->dbinfo;
}

/**
 * @brief DBConfigure::init 打开本地数据配置文件，读取配置参数
 */
void DBConfigure::init() {
  this->dbinfo = new list<struct dbDetails *>;
  std::string stringFromStream;
  ifstream in;
  in.open(this->dbconfigfile, ifstream::in);
  if (!in.is_open()) return;
  string line;
  while (getline(in, line)) {
    stringFromStream.append(line + "\n");
  }

  in.close();
  this->dbDoc = new Document();
  this->dbDoc->Parse(stringFromStream);
  if (this->dbDoc->HasParseError()) {
    rapidjson::ParseErrorCode code = this->dbDoc->GetParseError();
    qDebug() << code << endl;
  }
  Value &title = (*this->dbDoc)["TITLE"];
  Value &version = (*this->dbDoc)["VERSION"];

#ifdef MY_DEBUG_ON
  qDebug() << title.GetString() << endl;
  qDebug() << version.GetString() << endl;
#endif

  Value &details = (*this->dbDoc)["DETAILS"];
  for (size_t i = 0; i < details.Capacity(); i++) {
    struct dbDetails *dbitem = new dbDetails;
    Value &jsonItem = details[i];
    dbitem->ID = jsonItem["ID"].GetString();
    dbitem->TableName = jsonItem["TableName"].GetString();
    dbitem->Fields = jsonItem["FIELDS"].GetString();

#ifdef MY_DEBUG_ON
    qDebug() << "ID:\t" << jsonItem["ID"].GetString() << endl;
    qDebug() << "TableName:\t" << jsonItem["TableName"].GetString() << endl;
    qDebug() << "FIELDS:\t" << jsonItem["FIELDS"].GetString() << endl;
#endif

    if (jsonItem.HasMember("SQL")) {
      if (jsonItem["SQL"].IsString())
        qDebug() << "SQL:\t" << jsonItem["SQL"].GetString() << endl;
      if (jsonItem["SQL"].IsObject()) {
        dbitem->SQL = new map<std::string, std::string>;
        Value::MemberIterator i = jsonItem["SQL"].GetObject().begin();
        for (; i != jsonItem["SQL"].GetObject().end(); i++) {
          std::pair<std::string, std::string> *sqltmp =
              new std::pair<std::string, std::string>(i->name.GetString(),
                                                      i->value.GetString());
          dbitem->SQL->insert(*sqltmp);
#ifdef MY_DEBUG_ON
          qDebug() << i->name.GetString() << ":\t" << i->value.GetString()
                   << endl;
#endif
        }
      } else
        dbitem->SQL = nullptr;
    }

    this->dbinfo->push_back(dbitem);
  }
}

/**
 * @brief DBConfigure::getTableName 根据id获取该id对应表的表名
 * @param id
 * @return
 */
std::string DBConfigure::getTableName(std::string id) {
  if (id.empty()) return "";
  list<dbDetails *>::iterator i = this->dbinfo->begin();
  for (; i != this->dbinfo->end(); i++) {
    if ((*i)->ID == id) return (*i)->TableName;
  }
  return "";
}

/**
 * @brief DBConfigure::getFields 根据id获取该id对应表的字段名列表
 * @param id
 * @return
 */
std::string DBConfigure::getFields(std::string id) {
  if (id.empty()) return "";
  list<dbDetails *>::iterator i = this->dbinfo->begin();
  for (; i != this->dbinfo->end(); i++) {
    if ((*i)->ID == id) return (*i)->Fields;
  }
  return "";
}

/**
 * @brief DBConfigure::getSQL 根据id和key获取指定的sql配置字符串
 * @param id
 * @param key
 * @return
 */
std::string DBConfigure::getSQL(std::string id, std::string key) {
  if (id.empty() || key.empty()) return "";
  list<dbDetails *>::iterator i = this->dbinfo->begin();
  for (; i != this->dbinfo->end(); i++) {
    if ((*i)->ID == id) return (*i)->SQL->find(key)->second;
  }
  return "";
}
