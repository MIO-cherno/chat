#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");

        QString style = QLatin1String(qss.readAll());
        //QLatin1String 是一个用于存储和操作 Latin-1（也称为 ISO-8859-1）编码的字符串的类。
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("open failed");
    }

    w.show();
    return a.exec();
}
