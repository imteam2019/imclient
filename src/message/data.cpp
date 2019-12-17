#include "message/data.h"

using namespace std;
Data::Data() {}

/**
 * @brief Data::format
 * @param data
 * @param formatName
 * @return
 */
std::string Data::format(QMap<std::string, QVariant> *data, int formatName) {
  std::string *s;
  if (data == nullptr || data->count() <= 0 ||
      (formatName != Data::JSON && formatName != Data::XML)) {
    return nullptr;
  }
  s = new std::string();
  switch (formatName) {
    case Data::JSON:
      s = Data::formatAsJson(data, formatName);
      break;
    case Data::XML:
      s = Data::formatAsXml(data, formatName);
      break;
    default: {
      *s = "";
      break;
    }
  }
#ifdef MY_DEBUG_ON
  std::cout << "=========Encoded data =============" << endl;
  std::cout << s << endl;
#endif
  return *s;
}

std::string *Data::format(boost::unordered_map<std::string, boost::any> *data,
                          int formatName) {
  if (data == nullptr || data->size() == 0) return nullptr;

  // rapidjson::Document jsonDoc;         // JSON Document 指针
  rapidjson::StringBuffer jsonBuffer;  // JSON string buffer 指针
  rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(
      jsonBuffer);  // JSON Writer
  // jsonDoc.SetObject();
  // rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();

  // std::string key;
  boost::any value;
  for (boost::unordered_map<std::string, boost::any>::iterator itData =
           data->begin();
       itData != data->end(); ++itData) {
    // key = std::string(boost::any_cast<char *>(itData->first));
    value = itData->second;
    // std::cout << boost::typeindex::type_id<value>().pretty_name();
    if (value.type().operator==(typeid(int))) {
      int v = boost::any_cast<int>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.Int(v);
      jsonWriter.EndObject();
      continue;
    }

    if (value.type().operator==(typeid(int64_t))) {
      int64_t v = boost::any_cast<int64_t>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.Int64(v);
      jsonWriter.EndObject();
      continue;
    }

    if (value.type().operator==(typeid(unsigned int))) {
      unsigned int v = boost::any_cast<unsigned int>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.Uint(v);
      jsonWriter.EndObject();
      continue;
    }

    if (value.type().operator==(typeid(bool))) {
      bool v = boost::any_cast<bool>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.Bool(v);
      jsonWriter.EndObject();
      continue;
    }

    if (value.type().operator==(typeid(double))) {
      double v = boost::any_cast<double>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.Double(v);
      jsonWriter.EndObject();
      continue;
    }

    if (value.type().operator==(typeid(std::string))) {
      std::string v = boost::any_cast<std::string>(itData->second);
      jsonWriter.StartObject();
      jsonWriter.Key(itData->first);
      jsonWriter.String(v);
      jsonWriter.EndObject();
      continue;
    }
  }

  std::string *b = new std::string(jsonBuffer.GetString());
  return b;
}
/**
 * @brief Data::formatAsJson
 * @param data
 * @param formatName
 * @return
 */
std::string *Data::formatAsJson(QMap<std::string, QVariant> *data,
                                int formatName) {
  QMapIterator<std::string, QVariant> it(*data);
  std::string *s, key, value;
  /**
    {"username": "yhait", "password": "123456", "instruction":
    "111111111111111111111111", "telephone": "17775739032", "email":
    "yaozijian@foxmail.com"}
    */
  s = new std::string();
  s->append("{");
  while (it.hasNext()) {
    it.next();
    key = it.key();
    value = it.value().toString().toStdString();
    s->append("\"" + key + "\":\"");
    s->append(value + "\",");
  }
  s->append("}");
  key.clear();
  value.clear();
  return s;
}

std::string *Data::formatAsXml(QMap<std::string, QVariant> *data,
                               int formatName) {
  return nullptr;
}
