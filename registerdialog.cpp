#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QString>

#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    ui->passEdit->setEchoMode(QLineEdit::Password);
    ui->confirmEdit->setEchoMode(QLineEdit::Password);

    ui->errorTip->setProperty("state","normal");//给errorTip设置状态normal
    repolish(ui->errorTip);//更新errorTip的样式

    connect(ui->getCodeBtn,&QPushButton::clicked,this,&RegisterDialog::getCodeClicked);
}

void RegisterDialog::getCodeClicked()
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

RegisterDialog::~RegisterDialog()
{
    delete ui;
}


