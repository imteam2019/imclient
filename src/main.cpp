//#include "mainwindow.h"
#include <math.h>

#include <QApplication>
#include <cstdio>
#include <cstdlib>

#include "common/encrypt.h"
#include "login/signin.h"
#include "login/signup.h"
#include "mainwindow.h"
#include "message/data.h"
#include "message/message.h"
#include "network/tcpconn.h"

int main(int argc, char *argv[]) {
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
    "run by Elizabeth Queen (V “the Letter Not the Number” Lee.) There is of "
    "course Sharkespeare (Kevin “Overgrown Amoeba” Middleton) himself, the "
    "great white as it were, done up in full Sharktastic gear (compliments "
    "of Costumer Extraordinaire Deana Fisher Brill.) Middleton, who adapts "
    "the affected Shakespearean accent and format of over-speak, shuffles "
    "about on deck with his apprentice and protégé Shakesbear (Ellen “Bear "
    "Maximum” Jenkins.) Clad in a cuddly fur suit with a perfect glittery "
    "makeup plot to match, Jenkins spends the entire production up on deck "
    "as well, growling and making silly responses to everything that "
    "Middleton has to say. But fret not, ye viewers! Just because these two "
    "don’t swim, there yet be plenty of water activities involving "
    "submergence!\nI call this site the original Shakespeare blog for a good "
    "reason. Way way back in 2005, I wanted to talk about Shakespeare. I’d "
    "heard some kind of Shakespeare reference on the radio, I think it was "
    "on Howard Stern actually, and I was driving to work thinking, “Who do I "
    "know that would get that reference?”";

std::string *s = e.getBase64Encode(buf, strlen(buf), false);
cout << *s << endl << endl << endl;
cout << *(e.getBase64Decode(s->c_str(), s->size(), false)) << endl;
*/
}

/*
 *  // Encrypt::getMD5(Encrypt::getRandKey().toLocal8Bit());

Encrypt e;
QByteArray b =
    "网上有说明文长度小于等于密钥长度（Bytes）-"
    "11，这说法本身不太准确，会给人感觉RSA "
    "1024只能加密117字节长度明文。实际上，RSA算法本身要求加密内容也就是明文长"
    "度m必须0<m<n，也就是说内容这个大整数不能超过n，否则就出错。那么如果m="
    "0是什么结果？普遍RSA加密器会直接返回全0结果。如果m>"
    "n，运算就会出错？！那怎么办？且听下文分解。如果小于这个长度怎么办？就需"
    "要进行padding，因为如果没有padding，用户无法确分解密后内容的真实长度，字"
    "符串之类的内容问题还不大，以0作为结束符，但对二进制数据就很难理解，因为"
    "不确定后面的0是内容还是内容结束符。\n\nGo is expressive, concise, "
    "clean, and efficient. Its concurrency mechanisms make it easy to write "
    "programs that get the most out of multicore and networked machines, "
    "while its novel type system enables flexible and modular program "
    "construction. Go compiles quickly to machine code yet has the "
    "convenience of garbage collection and the power of run-time reflection. "
    "It's a fast, statically typed, compiled language that feels like a "
    "dynamically typed, interpreted "
    "language.\n\n香港美国商会会长塔拉·约瑟夫（Tara "
    "Joseph）7日晚对路透社声称，她在12月7日前往澳门，准备参加澳门美国商会的一"
    "场舞会时，被澳门出入境人员扣了2个小时，之后被拒绝入境。对此，澳门保安司"
    "司长黄少泽说，对具体个案不作评论。他还表示，过去已多次强调，每个国家、地"
    "区都有自身出入境政策，警方有义务、有责任确保澳门安全，口岸的控制方面亦如"
    "此。\n A new master plan unveiled Sunday on the integrated development "
    "of "
    "the Yangtze River Delta puts forward heavyweight measures to elevate "
    "the region's opening up across sectors, sending a fresh signal of "
    "China's determination to open its door wider.BEIJING, Dec. 3 (Xinhua) "
    "-- The Yangtze River Delta, one of China's fastest-growing and richest "
    "regions, is set to embrace more coordinated opening up efforts as a "
    "fertile ground of foreign investment and trade.A new master plan "
    "unveiled Sunday on the integrated development of region put forward "
    "heavyweight\n\nFileInfoHeader返回一个根据fi填写了部分字段的Header。 "
    "如果fi描述一个符号链接，FileInfoHeader函数将link参数作为链接目标。如果fi"
    "描述一个目录，会在名字后面添加斜杠。因为os."
    "FileInfo接口的Name方法只返回它描述的文件的无路径名，有可能需要将返回值的"
    "Name字段修改为文件的完整路径名。\n\nThere is a program, godoc, written "
    "in Go, that extracts package documentation from the source code and "
    "serves it as a web page with links to declarations, files, and so on. "
    "An instance is running at golang.org/pkg/. In fact, godoc implements "
    "the full site at golang.org/.\n\n原因在哪儿呢？其实此时疑惑有两处，\n"
    "第一"
    "，"
    "为什么两者无法通用\n第二，在提取代码的时候顺便看了看aes的实现，知道aes是"
    "每"
    "次16个字节运算一次，所以得出来的加密数据必然是16的整数倍。如果明文有9个"
    "字节，加密之后是16个字节这我知道。那解密的时候怎么知道原始数据的大小呢。"
    "毕竟版本包是用gzip压缩过的，差一个字节都没法正常解压缩出来。";

// std::cout << b.data() << endl;

// QByteArray c = "1234567890abcdefghijklmnopqrst";

  QString key = e.getRandKey();
  QByteArray *s = e.getAESEncrypt(b, key, 0);
  e.getAESDecrypt(*s, key, 0);
  e.generateRSAKey();
  QByteArray *d = e.getRSAEncrypt(b);
  e.getRSADecrypt(*d);

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
