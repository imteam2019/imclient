#include "data.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
using namespace rapidjson;
Data::Data()
{

}

/**
 * @brief Data::format
 * @param data
 * @param formatName
 * @return
 */
QString Data::format(QMap<QString,QVariant> *data,int formatName){
    QString *s;
    if(data==nullptr || data->count()<=0 || (formatName!=Data::JSON && formatName!=Data::XML)){
        return "";
    }
    s=new QString ();
    switch (formatName) {
        case Data::JSON :
            *s=Data::formatAsJson(data,formatName);
            break;
        case Data::XML :
            *s=Data::formatAsXml(data,formatName);
            break;
        default:{
            *s="";
            break;
        }
    }
    qDebug()<<*s<<endl;
    return *s;
}

/**
 * @brief Data::formatAsJson
 * @param data
 * @param formatName
 * @return
 */
QString Data::formatAsJson(QMap<QString, QVariant> *data, int formatName){
    QMapIterator<QString,QVariant> it(*data);
    QString s,key,value;
    /**
      {"username": "yhait", "password": "123456", "instruction": "111111111111111111111111", "telephone": "17775739032", "email": "yaozijian@foxmail.com"}
      */
    s.append("{");
    while (it.hasNext()) {
        it.next();
        key=it.key();
        value=it.value().toString();
        s.append("\""+key+"\":\"");
        s.append(value+"\",");
    }
    s.append("}");
    key.clear();
    value.clear();
   return s;
}


QString Data::formatAsXml(QMap<QString, QVariant> *data, int formatName){
    return "";
}
void Data::testJson(){
    const char json[] = "{ \"hello\" : \"world\" }";
    rapidjson::Document d;
    d.Parse<0>(json);

    printf("%s\n", d["hello"].GetString());
    return;
}
