#include "person.h"
#include "mainwindow.h"

Person::Person()
{
    this->strID=new QString;
    this->strNickName=new QString;
}

Person::Person(const Person& person){
    this->setID(*person.strID);
    this->setNickName(*person.strNickName);
}

Person::~Person(){
    delete this->strID;
    delete this->strNickName;
}

Person & Person::operator =(const Person &p)
{
    this->setID(*p.strID);
    this->setNickName(*p.strNickName);
    return *this;
}

bool Person::operator ==(const Person &p)
{
    if(QString::compare(*(p.strID),*(this->strID))==0 && QString::compare(*(p.strNickName),*(this->strNickName))==0)
        return true;
    else
        return false;
}

/**
 * @brief Person::getID
 * @return QString
 * @desc 返回当前的id
 */
QString Person::getID(){
    return *this->strID;
}

/**
 * @brief Person::getNickName
 * @return QString
 * @desc 返回当前昵称
 */
QString Person::getNickName(){
    return *this->strNickName;
}

/**
 * @brief Person::setID
 * @param id
 * @desc 设定指定id，如果为空则不修改
 */
void Person::setID(QString id){
    if(id.length()>0)
       *this->strID=id;
}

/**
 * @brief Person::setNickName
 * @param nickName
 * @desc 设定指定昵称，如果为空则不修改
 */
void Person::setNickName(QString nickName){
    if(nickName.length()>0)
        *this->strNickName=nickName;
}
