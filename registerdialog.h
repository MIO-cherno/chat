#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;

private:
    void showTip(QString str,bool state);

private slots:
    void get_code_clicked();
    void solt_reg_mod_finshed(ReqId id, QString res, ErrorCodes err);
    void initHttpHandlers();




private:
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTERDIALOG_H
