#include "friends.h"

Friends::Friends()
{
    //从本地加载好友列表
    this->plist=this->loadFriendFromLocal();
}

Friends::~Friends(){
    //将好友信息存入本地
    this->saveFriendtoLocal(this->plist);
    this->plist->clear();
}

/**
 * @brief Friend::add
 * @param p
 * @return bool
 * @desc 将新的好友加入，若传入指针为空指针，则返回false；
 */
bool Friends::add(Person *p){
    if(!p) return false;
    this->plist->append(*p);
    return true;
}


/**
 * @brief Friend::del
 * @param p
 * @return Person *
 * @desc 删除指定好友，如果当前好友列表中找不到，则返回空指针,若找到，则删除后返回原指针
 */
Person *Friends::del(Person *p){
    bool b=this->plist->isEmpty();
    if(b) return nullptr;
    Person *d=new Person;
    QMutableLinkedListIterator<Person> i(*this->plist);

    while (i.hasNext()) {
        d=&i.next();
        if(QString::compare((p->getID()),(d->getID()))==0){
            i.remove();
            break;
        }
    }
    return d;
}

/**
 * @brief Friends::find
 * @param id
 * @return Person *
 * @desc 按id找到指定的好友对象，如果列表为空，或者id为空，则返回空指针，找不到好友也返回为空指针；
 */
Person * Friends::find(QString id){
    if(id.length()<=0 || this->plist->isEmpty()) return nullptr;
    QMutableLinkedListIterator<Person> i(*this->plist);
    Person *p=new Person;
    while(i.hasNext()){
        p=&i.next();
        if(QString::compare((p->getID()),id)==0){
            break;
        }else
            p=nullptr;
    }
    return p;
}

QLinkedList<Person> * Friends::loadFriendFromLocal(){
    return nullptr;
}

QLinkedList<Person> * Friends::loadFriendFromRemote(){
    return nullptr;
}

bool Friends::saveFriendtoLocal(QLinkedList<Person> *plist){
    if(plist->isEmpty()) return false;
    return true;
}


bool Friends::saveFriendtoRemote(QLinkedList<Person> *plist){
    if(plist->isEmpty()) return false;
    return true;
}
