// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "frmProduct.h"
#include "ui_frmProduct.h"
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

#include "frmMain.h"
#include "dbcontroller.h"

frmProduct::frmProduct(QWidget *parent) : QDialog(parent), ui(new Ui::frmProduct) {
    ui->setupUi(this);

    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    LoadProductsToComboBox();

    ui->dteAdd->setDateTime(QDateTime::currentDateTime());
    ui->dteUpdate->setDateTime(QDateTime::currentDateTime());

    this->Clear();

}

frmProduct::~frmProduct()
{
    delete ui;
}


void frmProduct::Clear(){
    ui->txtBarcode->clear();
    ui->txtName->clear();
    ui->txtDescription->clear();
    ui->sbQuantity->clear();
    ui->sbPurchasePrice->clear();
    ui->sbSalePrice->clear();
    ui->cbReadonly->setChecked(false);
}

bool frmProduct::CheckInputs(){
    bool flag = true;

    if (ui->txtBarcode->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Barkod numarası boş bırakılamaz!");
        flag = false;
    } else if (ui->txtBarcode->text().trimmed().length() != 11) {
        QMessageBox::warning(this, "Ürün", "Barkod numarası 11 haneli olmalıdır!");
        flag = false;
    } else if (ui->txtName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Ürün ismi boş bırakılamaz!");
        flag = false;
    } else if (ui->txtDescription->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ürün", "Ürün açıklaması boş bırakılamaz!");
        flag = false;
    } else if (ui->sbQuantity->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün miktarını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbPurchasePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün satın alma fiyatını doğru şekilde giriniz!");
        flag = false;
    } else if (ui->sbSalePrice->value() <= 0.0) {
        QMessageBox::warning(this, "Ürün", "Ürün satış fiyatını doğru şekilde giriniz!");
        flag = false;
    }

    return flag;
}

void frmProduct::on_btnAdd_clicked()
{
    QString barcode = ui->txtBarcode->text().trimmed();
    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->toPlainText().trimmed();

    if(this->CheckInputs()){
        if(DBController::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
               "INSERT INTO "
               "product "
               "(barcode, name, description, quantity, purchasePrice, salePrice, dateAdd, dateUpdate) VALUES "
               "(:barcode, :name, :description, :quantity, :purchasePrice, :salePrice, NOW(), NOW())"
            );

            query.bindValue(":barcode", barcode);
            query.bindValue(":name", name);
            query.bindValue(":description", description);

            query.bindValue(":quantity", ui->sbQuantity->value());
            query.bindValue(":purchasePrice", ui->sbPurchasePrice->value());
            query.bindValue(":salePrice", ui->sbSalePrice->value());

            if(query.exec()){
                if(query.isActive()){
                    this->Clear();
                    this->Refresh();
                    ui->cbID->addItem(barcode);
                    QMessageBox::information(this, "Ürün", "Ürün başarıyla eklendi!");
                    qDebug() << "Database query OK.";
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Ürün eklenirken bir hata oluştu!");
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

void frmProduct::on_btnUpdate_clicked()
{
    QString barcode = ui->txtBarcode->text().trimmed();
    QString name = ui->txtName->text().trimmed();
    QString description = ui->txtDescription->toPlainText().trimmed();

    if(QString::compare(barcode, ui->cbID->currentText(), Qt::CaseSensitive) != 0){
        QMessageBox::warning(this, "Ürün", "Güncellenmek istenen ürünün barkodu değiştirilemez!");
        ui->txtBarcode->setText(ui->cbID->currentText());
        return;
    }

    if(this->CheckInputs()){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü güncellemek istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        } else if (reply == QMessageBox::Yes){
            if(DBController::instance()->IsOpen()){

                QSqlQuery query;

                query.prepare(
                   "UPDATE "
                   "product "
                   "SET name = :name, description = :description , quantity = :quantity, purchasePrice = :purchasePrice, salePrice = :salePrice, dateUpdate = NOW() "
                   "WHERE barcode = :barcode"
                );

                query.bindValue(":barcode", ui->cbID->currentText());
                query.bindValue(":name", name);
                query.bindValue(":description", description);
                query.bindValue(":quantity", ui->sbQuantity->value());
                query.bindValue(":purchasePrice", ui->sbPurchasePrice->value());
                query.bindValue(":salePrice", ui->sbSalePrice->value());

                if(query.exec()){
                    if(query.isActive()){
                        if(query.numRowsAffected() <= 0){
                            QMessageBox::warning(this, "Ürün", "İşlem sonucu boş (0) döndü!");
                            qDebug() << query.lastError();
                            return;
                        }
                        this->Refresh();
                        this->LoadProduct(ui->cbID->currentText());
                        QMessageBox::information(this, "Ürün", "Ürün başarıyla güncellendi!");
                        qDebug() << "Database query OK.";
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Ürün", "Ürün güncellenirken bir hata oluştu!");
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
}

void frmProduct::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü silmek istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    } else if (reply == QMessageBox::Yes){
        if(DBController::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
               "DELETE FROM "
               "product "
               "WHERE "
               "barcode = :barcode"
            );

            query.bindValue(":barcode", ui->cbID->currentText());

            if(query.exec()){
                if(query.isActive()){
                    if(query.numRowsAffected() <= 0){
                        QMessageBox::warning(this, "Ürün", "Ürün barkod hatası!");
                        qDebug() << query.lastError();
                        return;
                    }
                    this->Clear();
                    this->Refresh();
                    QMessageBox::information(this, "Ürün", "Ürün başarıyla silindi!");
                    qDebug() << "Database query OK.";
                    qDebug() << "Delete Product: " << ui->cbID->currentText();
                    ui->cbID->removeItem(ui->cbID->currentIndex());
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Ürün silinirken bir hata oluştu!");
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

void frmProduct::LoadProductsToComboBox(){

    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;
    query.exec("SELECT * FROM Product ORDER BY dateAdd");

    while (query.next()) {
        if(query.isActive()){
            int id = query.value(0).toInt();
            QString barcode = query.value(1).toString();


            ui->cbID->addItem(barcode);
        }
    }
}

void frmProduct::LoadProduct(const int index){
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "product "
       "ORDER BY "
       "ID "
       "LIMIT "
       ":index, 1"
    );

    query.bindValue(":index", index);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){
                ui->cbReadonly->setChecked(true);
                ui->cbID->setCurrentIndex(index);
                ui->txtBarcode->setText(query.value(1).toString());
                ui->txtName->setText(query.value(2).toString());
                ui->txtDescription->setText(query.value(3).toString());
                ui->sbQuantity->setValue(query.value(4).toInt());
                ui->sbPurchasePrice->setValue(query.value(5).toDouble());
                ui->sbSalePrice->setValue(query.value(6).toDouble());
                ui->dteAdd->setDateTime(query.value(7).toDateTime());
                ui->dteUpdate->setDateTime(query.value(8).toDateTime());
                qDebug() << "Load Product Index: " << index;
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Ürün getirilirken bir hata oluştu!");
        qDebug() << query.lastError();
        return;
    }
}

void frmProduct::LoadProduct(const QString barcode){
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "product "
       "WHERE "
       "barcode = :barcode"
    );

    query.bindValue(":barcode", barcode);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){
                ui->txtBarcode->setText(query.value(1).toString());
                ui->txtName->setText(query.value(2).toString());
                ui->txtDescription->setText(query.value(3).toString());
                ui->sbQuantity->setValue(query.value(4).toInt());
                ui->sbPurchasePrice->setValue(query.value(5).toDouble());
                ui->sbSalePrice->setValue(query.value(6).toDouble());
                ui->dteAdd->setDateTime(query.value(7).toDateTime());
                ui->dteUpdate->setDateTime(query.value(8).toDateTime());
                qDebug() << "Load Product: " << barcode;
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Ürün getirilirken bir hata oluştu!");
        qDebug() << query.lastError();
        return;
    }
}

void frmProduct::on_cbID_activated(int index)
{
    LoadProduct(ui->cbID->currentText());
}

void frmProduct::on_cbReadonly_stateChanged(int arg1)
{
    ui->txtBarcode->setReadOnly(m_isReadonly);
    ui->txtName->setReadOnly(m_isReadonly);
    ui->txtDescription->setReadOnly(m_isReadonly);
    ui->sbQuantity->setReadOnly(m_isReadonly);
    ui->sbPurchasePrice->setReadOnly(m_isReadonly);
    ui->sbSalePrice->setReadOnly(m_isReadonly);

    m_isReadonly = !m_isReadonly;
}
