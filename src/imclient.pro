QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# 自定义宏
DEFINES += MY_DEBUG_ON
DEFINES +=RAPIDJSON_HAS_STDSTRING

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/encrypt.cpp \
    compress/compress.cpp \
    compress/compressjpeg.cpp \
    friends.cpp \
    imtextedit.cpp \
    login/signin.cpp \
    login/signup.cpp \
    main.cpp \
    mainwindow.cpp \
    message/data.cpp \
    message/message.cpp \
    message/msghandle.cpp \
    network/httpconn.cpp \
    network/tcpconn.cpp \
    newfriend.cpp \
    person.cpp \
    settingshandle.cpp \

HEADERS += \
    common/encrypt.h \
    common/rapidjson/allocators.h \
    common/rapidjson/cursorstreamwrapper.h \
    common/rapidjson/document.h \
    common/rapidjson/encodedstream.h \
    common/rapidjson/encodings.h \
    common/rapidjson/error/en.h \
    common/rapidjson/error/error.h \
    common/rapidjson/filereadstream.h \
    common/rapidjson/filewritestream.h \
    common/rapidjson/fwd.h \
    common/rapidjson/internal/biginteger.h \
    common/rapidjson/internal/clzll.h \
    common/rapidjson/internal/diyfp.h \
    common/rapidjson/internal/dtoa.h \
    common/rapidjson/internal/ieee754.h \
    common/rapidjson/internal/itoa.h \
    common/rapidjson/internal/meta.h \
    common/rapidjson/internal/pow10.h \
    common/rapidjson/internal/regex.h \
    common/rapidjson/internal/stack.h \
    common/rapidjson/internal/strfunc.h \
    common/rapidjson/internal/strtod.h \
    common/rapidjson/internal/swap.h \
    common/rapidjson/istreamwrapper.h \
    common/rapidjson/memorybuffer.h \
    common/rapidjson/memorystream.h \
    common/rapidjson/msinttypes/inttypes.h \
    common/rapidjson/msinttypes/stdint.h \
    common/rapidjson/ostreamwrapper.h \
    common/rapidjson/pointer.h \
    common/rapidjson/prettywriter.h \
    common/rapidjson/rapidjson.h \
    common/rapidjson/reader.h \
    common/rapidjson/schema.h \
    common/rapidjson/stream.h \
    common/rapidjson/stringbuffer.h \
    common/rapidjson/writer.h \
    compress/compress.h \
    compress/compressjpeg.h \
    friends.h \
    imtextedit.h \
    login/signin.h \
    login/signup.h \
    mainwindow.h \
    message/data.h \
    message/message.h \
    message/msghandle.h \
    network/httpconn.h \
    network/tcpconn.h \
    newfriend.h \
    person.h \
    settingshandle.h \

FORMS += \
    login/signin.ui \
    login/signup.ui \
    mainwindow.ui \
    newfriend.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/release/ -lcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/debug/ -lcrypto
else:unix: LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/ -lcrypto

INCLUDEPATH += $$PWD/../../../../../usr/local/openssl/include
DEPENDPATH += $$PWD/../../../../../usr/local/openssl/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/release/libcrypto.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/debug/libcrypto.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/release/crypto.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/debug/crypto.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/libcrypto.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/release/ -lssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/debug/ -lssl
else:unix: LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/ -lssl

INCLUDEPATH += $$PWD/../../../../../usr/local/openssl/include
DEPENDPATH += $$PWD/../../../../../usr/local/openssl/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/release/libssl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/debug/libssl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/release/ssl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/debug/ssl.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/openssl/lib/libssl.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/release/ -lboost_container
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/debug/ -lboost_container
else:unix: LIBS += -L$$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/ -lboost_container

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/release/libboost_container.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/debug/libboost_container.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/release/boost_container.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/debug/boost_container.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/boost/1.71.0/lib/libboost_container.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/zlib/1.2.11/lib/release/ -lz.1.2.11
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/zlib/1.2.11/lib/debug/ -lz.1.2.11
else:unix: LIBS += -L$$PWD/../../../../../usr/local/Cellar/zlib/1.2.11/lib/ -lz.1.2.11

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/zlib/1.2.11/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/zlib/1.2.11/include

unix: LIBS += -L$$PWD/../../../../../usr/local/Cellar/jpeg-turbo/2.0.3/lib/ -lturbojpeg

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/jpeg-turbo/2.0.3/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/jpeg-turbo/2.0.3/include

unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/jpeg-turbo/2.0.3/lib/libturbojpeg.a
