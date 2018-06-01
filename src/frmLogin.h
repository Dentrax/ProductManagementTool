// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QDialog>

namespace Ui {
class frmLogin;
}

class frmLogin : public QDialog
{
    Q_OBJECT

public:
    explicit frmLogin(QWidget *parent = 0);
    ~frmLogin();

signals:
    void LoginOK(QString name);

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::frmLogin *ui;

    void closeEvent (QCloseEvent *event);
};

#endif // FRMLOGIN_H
