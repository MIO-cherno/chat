#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginDlg = new LoginDialog();
    setCentralWidget(loginDlg);
    loginDlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
