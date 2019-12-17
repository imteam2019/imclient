//#include "mainwindow.h"
#include <math.h>

#include <QApplication>
#include <cstdio>
#include <cstdlib>

#include "boost/any.hpp"
#include "boost/unordered_map.hpp"
#include "common/encrypt.h"
#include "login/signin.h"
#include "login/signup.h"
#include "mainwindow.h"
#include "message/data.h"
#include "message/message.h"
#include "network/tcpconn.h"

template <class T>
void foo(T) {
  std::cout << " Short name: " << boost::typeindex::type_id<T>().raw_name()
            << endl;
  std::cout << " Readable name: "
            << boost::typeindex::type_id<T>().pretty_name() << endl
            << endl
            << "================" << endl;
}

std::string *format(boost::unordered_map<std::string, boost::any> *data,
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
    qDebug() << value.type().name() << endl;
    foo(value);
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
int main(int argc, char *argv[]) {
  /*
  typedef boost::unordered_map<std::string, boost::any> unordered_map;
  unordered_map map;
  map.insert(unordered_map::value_type("Boris", 31));
  map.insert(unordered_map::value_type("Anton", "Testing char"));
  map.insert(unordered_map::value_type("Caesar", true));
  std::cout << *(format(&map, 0));

  // for (unordered_map::iterator it = map.begin(); it != map.end(); ++it) {
  // std::cout << "key-value:\t" << it->first;
  // std::cout<<it->second;
  /*
  int i;
  foo(i);
  long l;
  foo(l);

  unsigned int ui;
  foo(ui);

  unsigned long ul;
  foo(ul);

  char c;
  foo(c);

  char *by = "sldkfalskfdjalfd";
  foo(by);

  std::string s;
  foo(s);

  foo(by);
  foo(map);
  Message msg;
  foo(msg);

  boost::any a = msg;

  foo(a);
  std::cout << a.type().name() << endl;
  if (a.type().operator==(typeid(int))) std::cout << "Yes,it's int." << endl;
  if (a.type().operator==(typeid(std::string)))
    std::cout << "Yes,it's std::string." << endl;
  if (a.type().operator==(typeid(Message)))
    std::cout << "Yes,it's Message." << endl;

*/

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();

  /*
  Encrypt e;
  char buf[] =
   "To swim? Or not to swim! THAT is the question! And Fluid Movement has "
   "the answer with their annual summertime Water Ballet: SHARKESPEARE! "
   "Written collaboratively by Lynda Del Genis, Todd Gardner, Rachel "
   "Kassman, and Justin Sabe, with Kassman and Sabe serving as the show’s "
   "primary producers, this laugh-out-loud watery dorsal-fin approach to "
   "the Bard will have you in stitches with laughter over the terrible "
   "puns, the brilliant ideas, and in absolute awe at some of the "
   "synchronized swimming routines the execute in the vein of the Bard’s "
   "more popular "
   "tales."
   "\n目前Base64已经成为网络上常见的传输8Bit字节代码的编码方式之一。在做支付"
   "系统时，系统之间的报文交互都需要使用Base64对明文进行转码，然后再进行签名"
   "或加密，之后再进行（或再次Base64）传输。那么，Base64到底起到什么作用呢？"
   "\n在参数传输的过程中经常遇到的一种情况：使用全英文的没问题，但一旦涉及到"
   "中文就会出现乱码情况。与此类似，网络上传输的字符并不全是可打印的字符，比"
   "如二进制文件、图片等。Base64的出现就是为了解决此问题，它是基于64个可打印"
   "的字符来表示二进制的数据的一种方法。\n电子邮件刚问世的时候，只能传输英文"
   "，但后来随着用户的增加，中文、日文等文字的用户也有需求，但这些字符并不能"
   "被服务器或网关有效处理，因此Base64就登场了。随之，Base64在URL、Cookie、"
   "网页传输少量二进制文件中也有相应的使用。\nnonsense that the quartet of "
   "writers has spun together for this year’s "
   "aqua-visual feast! Genis, Gardner, Kassman, and Sabe have set the "
   "production at ‘The Globe Theatre Renaissance Festival and Water Park’ "
   "run by Elizabeth Queen (V “the Letter Not the Number” Lee.) There is of
  " "course Sharkespeare (Kevin “Overgrown Amoeba” Middleton) himself, the "
   "great white as it were, done up in full Sharktastic gear (compliments "
   "of Costumer Extraordinaire Deana Fisher Brill.) Middleton, who adapts "
   "the affected Shakespearean accent and format of over-speak, shuffles "
   "about on deck with his apprentice and protégé Shakesbear (Ellen “Bear "
   "Maximum” Jenkins.) Clad in a cuddly fur suit with a perfect glittery "
   "makeup plot to match, Jenkins spends the entire production up on deck "
   "as well, growling and making silly responses to everything that "
   "Middleton has to say. But fret not, ye viewers! Just because these two "
   "don’t swim, there yet be plenty of water activities involving "
   "submergence!\nI call this site the original Shakespeare blog for a good
  " "reason. Way way back in 2005, I wanted to talk about Shakespeare. I’d "
   "heard some kind of Shakespeare reference on the radio, I think it was "
   "on Howard Stern actually, and I was driving to work thinking, “Who do I
  " "know that would get that reference?”";

  std::string *s = e.getBase64Encode(buf, strlen(buf), false);
  cout << *s << endl << endl << endl;
  cout << *(e.getBase64Decode(s->c_str(), s->size(), false)) << endl;


  std::string b =
      "虽然人们发现在字符串表示中使用数字是很自然的，但计算机硬件更适合"
      "以二进制"
      "形式处理数字。这就是为什么当从键盘输入或从一个编辑过的文件中输入"
      "数字时，"
      "数字必须经过解析的原因。这也是为什么数字输出为让人查看的形式时必"
      "须进行格"
      "式化的原因。\n\n "
      "但是，有时候程序可能会将数据输出到一个只能被其他程序读取的文件，"
      "并且永远"
      "不会被人看到。在这些情况下，可以省略在输出期间格式化数字数据和在"
      "输入期间"
      "解析数字的过程。当数据以非格式化的形式写入时，即可以说它是以二进"
      "制形式编"
      "写的，用这种方式编写的文件可以称之为二进制文件。相反，保存格式化"
      "数据的文"
      "件则称为文本文件。\n\n为了方便程序员，流输入操作符 << "
      "在输出期间提供数字的自动格式化。同样，流提取操作符 >> "
      "提供数字输入的解析。例如，来看以下程序片段：\n\n\t ofstream "
      "file(\"num.dat\");\n\tshort x = 12 97;\n\tfile << "
      "x;\n\n最后一个语句将 "
      "x 的内容写入文件。然而，当数字被写入时，它将被存储为字符 "
      "'1'、'2'、'9' "
      "和 '7'，如图 1 所示。\n\n然而，数字 1297 并不以图 1 "
      "所示的方式存储在内存中（在变量 x "
      "中）。它被格式化为一个二进制数，在典型的 PC 上占用 2 个字节。图 "
      "2 "
      "显示了如何使用二进制或十六进制在内存中表示数字。\n\n 图 2 "
      "所示数字的未格式化表示是 \"原始\" "
      "数据存储在内存中的方式。信息可以按纯粹的二进制格式存储在文件中。"
      "存储的第"
      "一步是以二进制模式打开文件，其方法是使用 ios::binary "
      "标志。示例如下：\n\tfile.open(\"stuff.dat\", ios::out | "
      "ios::binary);\n\n请注意，ios::out 和 ios::binary "
      "标志使用|"
      "运算符联合加入到语句中，这导致文件以输出和二进制模式打开。";

  // std::cout << b.data() << endl;

  // QByteArray c = "1234567890abcdefghijklmnopqrst";
  Encrypt e;
  std::string key = e.getRandKey();

  std::string *plain = &b;

  std::string *ae = e.getAESEncrypt(plain, b.size(), key, 0);
  std::cout << "AES Encrypte is :\n" << *ae << endl;
  std::string *ad = e.getAESDecrypt(ae, ae->size(), key, 0);
  std::cout << "AES Decrypte is :\n" << *ad << endl;
  /* e.generateRSAKey();
   std::string *plain = &b;
   std::string *re = e.getRSAEncrypt(plain, b.size());
   std::cout << "RSA Encrypte is :\n" << *re << endl;
   std::string *rd = e.getRSADecrypt(re, re->length());
   std::cout << "RSA Decrypte is :\n" << *rd << endl;
  */

  /*
  QApplication a(argc, argv);
  Signup w;
  w.show();
  return a.exec();

  // Message a;
  //  printf("msg size:\t%ul\n", a.getMsgSize());
  // printf("msg header size:\t%ul\n", a.getMsgHeaderSize());
  //  printf("msg body size:\t%ul\n", a.getMsgBodySize());

  // char *s = "xixihahaxixihahaxixihahaxixihahaxixihahaxixihahaxixihaha";
  // a.setSenderID(s, strlen(s));
  // a.setReciverID(s, strlen(s));
  //  printf("msg size:\t%ul\n", a.getMsgSize());
  // printf("msg header size:\t%ul\n", a.getMsgHeaderSize());
  // printf("msg body size:\t%ul\n", a.getMsgBodySize());

  struct test {
  size_t msgHeaderLength;  //消息头长度
  size_t msgBodyLength;    //消息体长度
  char senderID[1024];     //发送方ID；
    // char c;
  char receiverID[1023];   //接收方ID;
  time_t sendTimes;  //消息发送时间，自Epoch（1970-01-01 00:00:00
    // UTC）起经过的时间，以秒为单位
  size_t status;     //消息当前状态
  size_t sendCount;  // 消息发送次数计数
  size_t msgType;    //消息类型，在线消息：0，离线消息：1
  };

  * Message m;
  MSGHeader h = *m.getMsgHeader();
  m.setSenderID("abcdefg", 7);
  std::cout << &m << endl;


  printf("message header size of is:\t %i\n", a.getMsgHeaderSize());
  a.setSenderID("123456789012345678901234567890", 30);

  printf("message header size of is:\t %i\n", a.getMsgHeaderSize());
  printf("test size of is:\t %i\n", sizeof(test));

  printf("message body size of is:\t %i\n", a.getMsgBodySize());
  a.setMsgContent(&b);
  printf("message body size of is:\t %i\n", a.getMsgBodySize());
  a.setMsgContent(&c);
  printf("message body size of is:\t %i\n", a.getMsgBodySize());
  a.setMsgContent(&c);
  printf("message body size of is:\t %i\n", a.getMsgBodySize());
  */
}
