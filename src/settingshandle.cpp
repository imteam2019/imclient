#include "settingshandle.h"

SettingsHandle::SettingsHandle()
{

}

 SettingsHandle::~SettingsHandle(){

}

/**
 * @brief SettingsHandle::loadSettings 按照指定的文件名加载其中的配置信息，并返回
 * @param fileName 配置文件名的指针
 * @param filetype 指定是何种数据格式的文件，目前只支持json或xml
 * @param isEncrypt 文件是否有加密
 * @return 装载配置关键字和值的QVariantMap对象指针，如果不成功则为空指针；
 */
QVariantMap * SettingsHandle::loadSettings(const QString *fileName, int filetype, bool isEncrypt){
    QVariantMap *sm=nullptr;
    //入参检查
    if(!fileName || fileName->length()<=0)
        return nullptr;
    if(filetype!=SettingsHandle::XML && filetype!=SettingsHandle::JSON){
        qDebug()<<"Error:filetype is not be support.\n"<<endl;
        return nullptr;
    }
    QFile file(*fileName);
    if(!file.exists()){
        qDebug()<<"Error:Not found the settings file.\n"<<endl;
        return nullptr;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
        return nullptr;
    }


    //读取文件
    QString *data=new QString();
    //qDebug()<<"file size:"<<this->sg->readAll()<<endl;
    //判断文件是否已经读到末尾了
    while(!file.atEnd()){
        char buffer[1024];
        //读取一行数据
        qint64 length = file.readLine(buffer,1024);
        if(length != -1){
            qDebug()<<buffer;
            data->append(buffer);
        }
    }

    if(data->length()<=0){
        qDebug()<<"the settings file has nothing.\n"<<endl;
        return nullptr;
    }

    if(isEncrypt){
        //todo:此处对data内容进行解密处理
    }

    switch (filetype) {
        case SettingsHandle::JSON:
            sm=  this->loadJson(data);
        break;
        case SettingsHandle::XML:
            sm= this->loadXml(data);
        break;
    }

    file.close();
    delete &file;

    return sm;

}

/**
 * @brief SettingsHandle::loadJson 将Json字符串原文转换成QVariantMap对象
 * @param data 字符串，Json数据
 * @return QVariantMap指针，失败则为空指针
 */
QVariantMap * SettingsHandle::loadJson(QString *data){
    if(!data || data->length()<=0) return nullptr;

    QVariantMap *sm=new QVariantMap();

    QJsonParseError error;
    QJsonDocument jd = QJsonDocument::fromJson(data->toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jd.isObject()) {
            *sm= jd.toVariant().toMap();
        }
    } else {
        qFatal(error.errorString().toUtf8().constData());
    }
    return sm;
}


/**
 * @brief SettingsHandle::loadXml 将Xml字符串原文转换成QVariantMap对象
 * @param data 字符串，Json数据
 * @return QVariantMap指针，失败则为空指针
 */
QVariantMap * SettingsHandle::loadXml(QString *data){
    if(!data || data->length()<=0) return nullptr;

    QVariantMap *sm=new QVariantMap();

   //todo:xml转化实现
    return sm;
}
