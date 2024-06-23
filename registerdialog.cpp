#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QString>

#include "global.h"
#include "httpmgr.h"    //自己的头文件尽量在要使用的cpp引用，防止互引用

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    ui->passEdit->setEchoMode(QLineEdit::Password);
    ui->confirmEdit->setEchoMode(QLineEdit::Password);

    ui->errorTip->setProperty("state","normal");//给errorTip设置状态normal
    repolish(ui->errorTip);//更新errorTip的样式

    connect(ui->getCodeBtn,&QPushButton::clicked,this,&RegisterDialog::get_code_clicked);

    //? why is "HttpMgr::GetInstance().get()"
    //HttpMgr::GetInstance()是HttpMgr的智能指针，get是获取智能指针的裸指针
    //裸指针是指智能指针类内部持有的、用于管理对象的实际指针
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

void RegisterDialog::get_code_clicked()
{
    auto email = ui->emailEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"),false);
    }
}

void RegisterDialog::showTip(QString str,bool state)
{
    if(state)
    {
        ui->errorTip->setProperty("state","normal");
    }
    else{
        ui->errorTip->setProperty("state","err");
    }

    ui->errorTip->setText(str);
    repolish(ui->errorTip);
}

void RegisterDialog::slot_reg_mod_finsh(ReqId id, QString res, ErrorCodes err)
{
    //error
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());//byte->jsonDoc
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();//jsonDoc->jsonObj


    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    //function:先把注册及其对注册所做出的反应插入_handlers,以便之后根据id调用
    //注册获取验证码回包逻辑
    //map的insert参数要为键值对
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject& jsonObj){
        //可以捕获this ，因为qt会自动维护生命周期，保证RegisterDialog在其生命周期内不被销毁
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });
}



RegisterDialog::~RegisterDialog()
{
    delete ui;
}


