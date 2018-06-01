// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "frmRegister.h"
#include "ui_frmRegister.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QLabel>
#include <QDebug>
#include <QSqlError>
#include <QRegExp>

#include "dbcontroller.h"

frmRegister::frmRegister(QWidget *parent) : QDialog(parent), ui(new Ui::frmRegister) {
    ui->setupUi(this);

    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

frmRegister::~frmRegister()
{
    this->setFixedSize(this->width(),this->height());
    delete ui;
}

bool frmRegister::CheckInputs(){
    QString name = ui->txtName->text().trimmed();
    QString surname = ui->txtSurname->text().trimmed();
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();
    QString password2 = ui->txtPassword2->text().trimmed();
    QString mailAddress = ui->txtMail->text().trimmed();
    QString mobilePhone = ui->txtPhoneNumber->text().trimmed();
    QString homeAddress = ui->txtAddress->toPlainText().trimmed();

    bool flag = true;

    QRegExp regexMail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    regexMail.setCaseSensitivity(Qt::CaseInsensitive);
    regexMail.setPatternSyntax(QRegExp::RegExp);

    QRegExp regexPhone("^[0-9]{10}$");
    regexPhone.setCaseSensitivity(Qt::CaseInsensitive);
    regexPhone.setPatternSyntax(QRegExp::RegExp);

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "İsim boş bırakılamaz!");
        flag = false;
    } else if (surname.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Soyad boş bırakılamaz!");
        flag = false;
    } else if (username.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Kullanıcıadı boş bırakılamaz!");
        flag = false;
    } else if (password.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Şifre boş bırakılamaz!");
        flag = false;
    } else if (password2.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Şifre boş bırakılamaz!");
        flag = false;
    } else if (QString::compare(password, password2, Qt::CaseSensitive) != 0) {
        QMessageBox::warning(this, "Kayıt", "Şifreler eşleşmiyor!");
        flag = false;
    } else if (mailAddress.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Mail adresi boş bırakılamaz!");
        flag = false;
    } else if (!regexMail.exactMatch(mailAddress)) {
        QMessageBox::warning(this, "Kayıt", "Lütfen mail adresinizi doğru şekilde giriniz!");
        flag = false;
    } else if (mobilePhone.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Telefon numarasaı boş bırakılamaz!");
        flag = false;
    } else if (!regexPhone.exactMatch(mobilePhone)) {
        QMessageBox::warning(this, "Kayıt", "Lütfen telefon numaranızı doğru şekilde ve 11 hane olarak giriniz!");
        flag = false;
    } else if (homeAddress.isEmpty()) {
        QMessageBox::warning(this, "Kayıt", "Ev adresi boş bırakılamaz!");
        flag = false;
    } else if (!ui->chkTermsOfService->checkState()) {
        QMessageBox::warning(this, "Kayıt", "Lütfen kayıt şartlarını kabul ediniz!");
        flag = false;
    }

    return flag;
}

void frmRegister::Clear(){
    ui->txtName->clear();
    ui->txtSurname->clear();
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->txtPassword2->clear();
    ui->txtMail->clear();
    ui->txtPhoneNumber->clear();
    ui->txtAddress->clear();
}

void frmRegister::on_btnRegister_clicked()
{
    if(this->CheckInputs()){
        if(DBController::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
               "INSERT INTO "
               "user "
               "(username, password, name, surname, phone, mail, address, dateRegister, dateLastLogin, authorityLevel) "
               "VALUES "
               "(:username, :password, :name, :surname, :phone, :mail, :address, NOW(), NOW(), :authorityLevel)"
            );

            query.bindValue(":username", ui->txtUsername->text().trimmed());
            query.bindValue(":password", ui->txtPassword->text().trimmed());
            query.bindValue(":name", ui->txtName->text().trimmed());
            query.bindValue(":surname", ui->txtSurname->text().trimmed());
            query.bindValue(":phone", ui->txtPhoneNumber->text().trimmed());
            query.bindValue(":mail", ui->txtMail->text().trimmed());
            query.bindValue(":address", ui->txtAddress->toPlainText().trimmed());
            query.bindValue(":authorityLevel", 1);

            if(query.exec()){
                if(query.isActive()){
                    this->Clear();
                    QMessageBox::information(this, "Kayıt", "Kullanıcı kayıdı başarılı!");
                    qDebug() << "Database query OK.";
                    this->close();
                    return;
                }
            } else {
                QMessageBox::warning(this, "Kayıt", "Kullanıcı kaydı sırasında bir hata oluştu!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı kapalı!");
            qDebug() << "Database connection closed.";
            return;
        }
    }
}
