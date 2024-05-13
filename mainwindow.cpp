#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginDlg = new LoginDialog(this);
    /*参数为this，使LoginDialog继承父类mainwindow，便于内存管理
     * 关掉父类时，其子类都会被销毁
    */
    setCentralWidget(loginDlg);


    //创建注册消息链接
    registerDlg = new RegisterDialog(this);
    //当 loginDlg 对象的 switchRegister 信号被发射时，调用当前 MainWindow 对象的 slotSwitchReg 槽函数。
    connect(loginDlg,&LoginDialog::switchRegister,this,&MainWindow::slotSwitchReg);

    //将LoginDialog继承mainwindow后，导致LoginDialog窗口脱离,解决方法之一是将LoginDialog设置为无边框
    loginDlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    /*Qt::FramelessWindowHint 标志用于创建一个无边框的窗口。
     *Qt::CustomizeWindowHint 标志允许你自定义窗口的某些非标准特性。
     *然而，这个标志本身并不直接改变窗口的外观或行为；它通常与其他标志一起使用，
     *以指示窗口系统允许应用程序执行一些非标准的窗口操作。
    */
    registerDlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    registerDlg->hide();

}

void MainWindow::slotSwitchReg()
{
    setCentralWidget(registerDlg);
    loginDlg->hide();
    registerDlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;

    // if(loginDlg){
    //     delete loginDlg;
    //     loginDlg = nullptr;
    // }
    // if(registerDlg){
    //     delete registerDlg;
    //     registerDlg = nullptr;
    // }
}
