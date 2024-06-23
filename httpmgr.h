#ifndef HTTPMGR_H
#define HTTPMGR_H


#include "singleton.h"

#include <QString>
#include <QUrl>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
//crtp 奇异递归
class HttpMgr:public QObject, public Singleton<HttpMgr>,
                public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    /*
     * Q_OBJECT宏是一个非常重要的宏，它几乎在每个继承自QObject或其子类的类定义中都会出现。
     * 信号和槽机制、属性系统、对象树和父子关系、事件过滤器等
    */


private:
    HttpMgr();
    friend class Singleton<HttpMgr>;
    //基类设置为友元，可以访问HttpMgr的构造函数。因为模板

    QNetworkAccessManager _manger;
    void postHttpReq(QUrl url,QJsonObject json,ReqId reqId,Modules mod);//发送http请求

private slots://槽
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals://信号
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);//return result
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);//注册（register）
public:
    ~HttpMgr();
    /******************************************************************************
    *当一个派生类（子类）的对象被销毁时，首先会调用派生类的析构函数，然后会自动调用
    *其基类（父类）的析构函数（如果有的话）。这个过程是递归的，会一直向上追溯到最顶层的基类。
    *
    *httpmgr析构会调用singleton的析构，singleton的成员shared_ptr又会调用智能指针的析构
    *智能指针为模板类，又要调用T类型的析构函数，由于T类型在这里是HttpMgr，所以会调用
    *httpmgr的析构，所以要把httpmgr的析构设为public
    *****************************************************************************/
}

#endif //HTTPMGR_H
