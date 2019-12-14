#include "friends.h"

Friends::Friends() {
  //从本地加载好友列表
  this->fmap = this->loadFriendFromLocal();
}

Friends::~Friends() {
  //将好友信息存入本地
  this->saveFriendtoLocal(this->fmap);
  this->fmap->clear();
  delete this->fmap;
}

/**
 * @brief Friend::add
 * @param p
 * @return bool
 * @desc 将新的好友加入，若传入指针为空指针，则返回false；
 */
bool Friends::add(Person *p) {
  if (!p) return false;
  if (this->fmap == nullptr) this->fmap = new MAPFRIENDS();
  this->fmap->at(p->getID()) = *p;
  return true;
}

/**
 * @brief Friend::del
 * 删除指定好友，如果当前好友列表中找不到，则返回空指针,若找到，则删除后返回原指针
 * @param p
 * @return Person *
 *
 */
Person *Friends::del(Person *p) {
  if (this->fmap->empty() || p == nullptr) return nullptr;
  Person *d = new Person();
  *d = this->fmap->at(p->getID());
  this->fmap->erase(p->getID());
  return d;
}

/**
 * @brief Friends::find
 * 按id找到指定的好友对象，如果列表为空，或者id为空，则返回空指针，找不到好友也返回为空指针；
 * @param id
 * @return Person *
 *
 */
Person *Friends::find(std::string id) {
  if (id.length() <= 0 || this->fmap->empty()) return nullptr;
  Person *p = new Person();
  *p = this->fmap->at(id);
  return p;
}

MAPFRIENDS *Friends::loadFriendFromLocal() {
  // TODO
  return nullptr;
}

MAPFRIENDS *Friends::loadFriendFromRemote() {
  // TODO
  return nullptr;
}

bool Friends::saveFriendtoLocal(MAPFRIENDS *plist) {
  if (plist->empty()) return false;
  return true;
}

bool Friends::saveFriendtoRemote(MAPFRIENDS *plist) {
  if (plist->empty()) return false;
  return true;
}
