QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RC_ICONS = icon.ico
DESTDIR = ./bin
#在设置 DESTDIR 变量，它指定了构建目标（如可执行文件、库等）应该被放置的目录。
#在这个例子中，构建目标将被放置在项目目录下的 bin 子目录中。这是 Qt 构建系统的一个标准变量，通常用于控制构建输出的位置。

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    logindialog.h \
    mainwindow.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc
