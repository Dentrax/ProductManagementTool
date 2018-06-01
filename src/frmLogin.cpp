// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "frmLogin.h"
#include "ui_frmLogin.h"
#include "frmRegister.h"
#include "frmMain.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QLabel>
#include "dbcontroller.h"
#include <QApplication>
#include <QSqlError>
#include <QDebug>
#include <QCloseEvent>

frmLogin::frmLogin(QWidget *parent) : QDialog(parent), ui(new Ui::frmLogin)
{
    qApp->setQuitOnLastWindowClosed(false);

    ui->setupUi(this);
    window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window()->size(), qApp->desktop()->availableGeometry()));

    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    if(DBController::instance()->IsOpen()){
        ui->lblStatus->setText("Database connection succeeded!");
        QTextStream(stdout) << "Connect OK!";
    } else {
        ui->lblStatus->setText("Database connection fault!");
        QTextStream(stdout) << "Connect Fail!";
    }
}

frmLogin::~frmLogin()
{
    this->setFixedSize(this->width(),this->height());
    delete ui;
}

void frmLogin::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Ürün Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (mboxSelect != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

void frmLogin::on_btnRegister_clicked()
{
    frmRegister *r = new frmRegister(this);
    r->setModal(true);
    r->show();
}

void frmLogin::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();


    if (username.isEmpty()) {
        ui->lblStatus->setText("Kullanıcıadı boş bırakılamaz!");
        return;
    } else if (password.isEmpty()) {
        ui->lblStatus->setText("Şifre boş bırakılamaz!");
        return;
    }

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "user "
       "WHERE "
       "username = :username AND password = :password"
    );

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if(query.exec()){
        if(query.isActive()){
            int count = 0;

            while(query.next()){
                count++;
            }

            if(count == 1){
                ui->lblStatus->setText("Giriş başarılı.");
                this->hide();
                this->LoginOK(username);
                return;
            } else if (count > 1){
                ui->lblStatus->setText("Birden fazla Kullanıcıadı ve Şifre tespit edildi.");
            } else if (count < 1){
                ui->lblStatus->setText("Geçersiz Kullanıcıadı ve Şifre");
            }
        } else {
            ui->lblStatus->setText("Query aktif değil!");
            qDebug() << query.lastError();
        }
    } else {
        ui->lblStatus->setText("Veritabanı hatası oluştu.");
        qDebug() << query.lastError();
    }


}

