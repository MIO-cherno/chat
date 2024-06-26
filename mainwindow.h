#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口
 *
 * @author     MIO-Cherno
 * @date       2024/05/12
 * @history
 *****************************************************************************/

#include <QMainWindow>

#include "logindialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private:
    LoginDialog *loginDlg;
    RegisterDialog *registerDlg;


public:
    void slotSwitchReg();
};
#endif // MAINWINDOW_H
