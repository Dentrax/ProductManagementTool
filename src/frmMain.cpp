// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "frmMain.h"
#include "ui_frmMain.h"
#include "QSqlQueryModel"
#include "frmProduct.h"
#include "frmAbout.h"
#include "frmLogin.h"
#include <QTextStream>
#include "dbcontroller.h"
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QAction>
#include <QString>
#include <QSqlError>
#include <QCloseEvent>
#include <QDateTimeEdit>
#include <QDateTime>

frmMain::frmMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmMain){
    this->setVisible(false);
    this->hide();

    ui->setupUi(this);
    window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window()->size(), qApp->desktop()->availableGeometry()));
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->dteSearchByDateAddMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateAddMax->setDateTime(QDateTime::currentDateTime());

    ui->dteSearchByDateUpdateMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMax->setDateTime(QDateTime::currentDateTime());

    ui->tblProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblProducts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblProducts->resizeColumnsToContents();
    ui->tblProducts->resizeRowsToContents();
    ui->tblProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tblProducts->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);

    ui->txtSearchByName->setEnabled(false);
    ui->cbSearchByNamePattern->setEnabled(false);
    ui->cbSearchByDateAdd->setEnabled(false);
    ui->cbSearchByDateUpdate->setEnabled(false);
    ui->dteSearchByDateAddMin->setEnabled(false);
    ui->dteSearchByDateAddMax->setEnabled(false);
    ui->dteSearchByDateUpdateMin->setEnabled(false);
    ui->dteSearchByDateUpdateMax->setEnabled(false);
    ui->sbSearchByQuantity->setEnabled(false);
    ui->cbSearchByQuantityPattern->setEnabled(false);
    ui->cbSearchByPricePurchase->setEnabled(false);
    ui->cbSearchByPriceSale->setEnabled(false);
    ui->dsbSearchByPricePurchase->setEnabled(false);
    ui->cbSearchByPricePurchasePattern->setEnabled(false);
    ui->dsbSearchByPriceSale->setEnabled(false);
    ui->cbSearchByPriceSalePattern->setEnabled(false);


    DBController::instance()->SetupDB();

    if(DBController::instance()->Connect()){
        QTextStream(stdout) << "Connect OK!";
    } else {
        QTextStream(stdout) << "Connect Fail!";
    }


    m_frmProduct = new frmProduct(this);
    m_frmLogin = new frmLogin(this);

    bool signalAbout = connect(ui->actAbout, SIGNAL(triggered()), this, SLOT(showMenuAbout()));
    Q_ASSERT(signalAbout);

    bool signalQuit = connect(ui->actQuit, SIGNAL(triggered()), this, SLOT(quitApp()));
    Q_ASSERT(signalAbout);

    bool signalOK = connect(m_frmProduct, SIGNAL(Refresh()), this, SLOT(on_btnRefresh_clicked()));
    Q_ASSERT(signalOK);

    bool signalAccount = connect(m_frmLogin, SIGNAL(LoginOK(QString)), this, SLOT(loginOKWith(QString)));
    Q_ASSERT(signalAccount);

    m_frmLogin->show();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Ürün Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (mboxSelect != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        quitApp();
    }
}

void frmMain::quitApp(){
    try {
        QMessageBox::StandardButton mboxSelect = QMessageBox::question( this, "Ürün Takip Yazılımı", "Çıkmak istediğinizden emin misiniz?", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

        if (mboxSelect != QMessageBox::Yes) {
            return;
        } else {
            if(DBController::instance()->IsOpen()){
                DBController::instance()->Disconnect();
            }
            QApplication::quit();
        }
    } catch (...) {
        qDebug() << "Hata";
        QApplication::exit(1);
    }
}

void frmMain::showMenuAbout()
{
    frmAbout * frm = new frmAbout();
    frm->setModal(true);
    frm->show();

    qDebug() << "Show Form About";
}

void frmMain::loginOKWith(QString name){
    m_frmLogin->hide();
    this->show();
    this->setVisible(true);
    this->setWindowOpacity(1);

    if(DBController::instance()->IsOpen()){
        ui->statusbar->showMessage("Successully connected to MySQL database.", 1000);
        QTextStream(stdout) << "Connect OK!";

        LoadProducts();
    } else{
        QMessageBox::critical(this, "ERROR", DBController::instance()->GetError());
        QTextStream(stdout) << "Connect Fail!";
    }

    ui->lblAccountInfo->setText("Welcome, " + name);
}

void frmMain::LoadProducts(){
    qDebug() << "LoadProducts CALL";

    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "product"
    );

    if (query.exec()){
        if(query.isActive()){
            qDebug() << "LoadProducts OK";
            queryModel->setQuery(query);

            queryModel->setHeaderData(0, Qt::Horizontal, "ID");
            queryModel->setHeaderData(1, Qt::Horizontal, "Barcode");
            queryModel->setHeaderData(2, Qt::Horizontal, "Name");
            queryModel->setHeaderData(3, Qt::Horizontal, "Description");
            queryModel->setHeaderData(4, Qt::Horizontal, "Quantity");
            queryModel->setHeaderData(5, Qt::Horizontal, "Purchase Price");
            queryModel->setHeaderData(6, Qt::Horizontal, "Sale Price");
            queryModel->setHeaderData(7, Qt::Horizontal, "Add Date");
            queryModel->setHeaderData(8, Qt::Horizontal, "Update Date");

            ui->tblProducts->setModel(queryModel);
            ui->statusbar->showMessage("LoadProducts() success: " + queryModel->rowCount());
        } else {
            QMessageBox::critical(this, "ERROR", "Query aktif değil!");
            qDebug() << query.lastError();
            return;
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Ürün getirilirken bir hata oluştu!");
        qDebug() << query.lastError();
        return;
    }



}

void frmMain::on_btnRefresh_clicked()
{
    this->LoadProducts();
}

void frmMain::on_btnProductOperations_clicked()
{    
    m_frmProduct->setModal(true);
    m_frmProduct->show();
    m_frmProduct->Clear();
}

void frmMain::on_tblProducts_activated(const QModelIndex &index)
{
    m_frmProduct->setModal(true);
    m_frmProduct->show();
    m_frmProduct->LoadProduct(index.row());
}

void frmMain::on_tblProducts_pressed(const QModelIndex &index)
{
    LoadProductInfoToLabel(index);
}

void frmMain::LoadProductInfoToLabel(const QModelIndex &index){
    QSqlQueryModel * queryModel = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare(
       "SELECT * FROM "
       "product "
       "WHERE "
       "id = :id AND barcode = :barcode"
    );

    query.bindValue(":id", index.sibling(index.row(), 0).data().toInt());
    query.bindValue(":barcode", index.sibling(index.row(), 1).data().toString());

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){

                ui->lblProductInfo->setText("Barcode: " + query.value(1).toString() + " - " + index.model()->headerData(index.column(), Qt::Horizontal).toString() + ": " + index.sibling(index.row(), index.column()).data().toString());

                qDebug() << "Load Product Info: " << query.executedQuery();
            }
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Ürün getirilirken bir hata oluştu!");
        qDebug() << query.lastError();
        return;
    }
}


void frmMain::on_btnSearch_clicked()
{
    QString queryString = "SELECT * FROM product ";
    QString queryStringWhereConcatenator = "WHERE ";

    if(ui->cbSearchByName->checkState()){
        QString productName = ui->txtSearchByName->text().trimmed();
        if(!productName.isEmpty() && productName.length() > 0){
            queryString += queryStringWhereConcatenator;
            if(ui->cbSearchByNamePattern->currentIndex() == 0){ //Exactly
                queryString += "name = '" + productName + "' ";
            } else if (ui->cbSearchByNamePattern->currentIndex() == 1){ //Stars With
                queryString += "name like '" + productName + "%' ";
            } else if (ui->cbSearchByNamePattern->currentIndex() == 2){ //Ends With
                queryString += "name like '%" + productName + "' ";
            }
            queryStringWhereConcatenator = "AND ";
        } else {
            QMessageBox::warning(this, "Search", "SearchByName option selected but text is null or empty!");
            return;
        }
    }

    if(ui->cbSearchByDate->checkState()){
        QString time_format = "yyyy-MM-dd  HH:mm:ss";

        if(ui->cbSearchByDateAdd->checkState()){
            QDateTimeEdit* min = ui->dteSearchByDateAddMin;
            QDateTimeEdit* max = ui->dteSearchByDateAddMax;

            QString smin = min->dateTime().toString(time_format);
            QString smax = max->dateTime().toString(time_format);

            queryString += queryStringWhereConcatenator;
            queryString += "dateAdd BETWEEN = " + smin + " AND " + smax + " ";
            queryStringWhereConcatenator = "AND ";
        }
        if(ui->cbSearchByDateUpdate->checkState()){
            QDateTimeEdit* min = ui->dteSearchByDateUpdateMin;
            QDateTimeEdit* max = ui->dteSearchByDateUpdateMax;

            QString smin = min->dateTime().toString(time_format);
            QString smax = max->dateTime().toString(time_format);

            queryString += queryStringWhereConcatenator;
            queryString += "dateUpdate BETWEEN '" + smin + "' AND '" + smax + "' ";
            queryStringWhereConcatenator = "AND ";
        }
    }

    if(ui->cbSearchByQuantity->checkState()){
        if(ui->sbSearchByQuantity->value() > 0){
            queryString += queryStringWhereConcatenator;
            if(ui->cbSearchByQuantityPattern->currentIndex() == 0){ //LOWER
                queryString += "quantity <= " + QString::number(ui->sbSearchByQuantity->value()) + " ";
            }else if(ui->cbSearchByQuantityPattern->currentIndex() == 1){ //HIGHER
                queryString += "quantity >= " + QString::number(ui->sbSearchByQuantity->value()) + " ";
            }
            queryStringWhereConcatenator = "AND ";
        }else{
            QMessageBox::warning(this, "Search", "SearchByQuantity option selected but value must be higher than 0!");
            return;
        }

    }

    if(ui->cbSearchByPrice->checkState()){
        if(ui->cbSearchByPricePurchase->checkState()){
            if(ui->dsbSearchByPricePurchase->value() > 0.0){
                queryString += queryStringWhereConcatenator;
                if(ui->cbSearchByPricePurchasePattern->currentIndex() == 0){ //LOWER
                    queryString += "purchasePrice <= " + QString::number(ui->dsbSearchByPricePurchase->value()) + " ";
                }else if(ui->cbSearchByPricePurchasePattern->currentIndex() == 1){ //HIGHER
                    queryString += "purchasePrice >= " + QString::number(ui->dsbSearchByPricePurchase->value()) + " ";
                }
                queryStringWhereConcatenator = "AND ";
            }else{
                QMessageBox::warning(this, "Search", "SearchByPricePurchase option selected but value must be higher than 0.0!");
                return;
            }

        }
        if(ui->cbSearchByPriceSale->checkState()){
            if(ui->dsbSearchByPriceSale->value() > 0.0){
                queryString += queryStringWhereConcatenator;
                if(ui->cbSearchByPriceSalePattern->currentIndex() == 0){ //LOWER
                    queryString += "salePrice <= " + QString::number(ui->dsbSearchByPriceSale->value()) + " ";
                }else if(ui->cbSearchByPriceSalePattern->currentIndex() == 1){ //HIGHER
                    queryString += "salePrice >= " + QString::number(ui->dsbSearchByPriceSale->value()) + " ";
                }
                queryStringWhereConcatenator = "AND ";
            }else{
                QMessageBox::warning(this, "Search", "SearchByPriceSale option selected but value must be higher than 0.0!");
                return;
            }
        }
    }

    qDebug() << "Search Query: " << queryString;

    QSqlQuery query;
    query.prepare(queryString);

     QSqlQueryModel * queryModel = new QSqlQueryModel();

     if (query.exec()){
         if(query.isActive()){
             qDebug() << "Search OK";
             queryModel->setQuery(query);

             queryModel->setHeaderData(0, Qt::Horizontal, "ID");
             queryModel->setHeaderData(1, Qt::Horizontal, "Barkod");
             queryModel->setHeaderData(2, Qt::Horizontal, "Ürün");
             queryModel->setHeaderData(3, Qt::Horizontal, "Açıklama");
             queryModel->setHeaderData(4, Qt::Horizontal, "Adet");
             queryModel->setHeaderData(5, Qt::Horizontal, "Alış Fiyatı");
             queryModel->setHeaderData(6, Qt::Horizontal, "Satış Fiyatı");
             queryModel->setHeaderData(7, Qt::Horizontal, "Eklenme Tarihi");
             queryModel->setHeaderData(8, Qt::Horizontal, "Güncelleme Tarihi");

             ui->tblProducts->setModel(queryModel);

             ui->twMain->setCurrentIndex(0);

             ui->statusbar->showMessage("Search() success: " + queryModel->rowCount());
         } else {
             QMessageBox::critical(this, "ERROR", "Query aktif değil!");
             qDebug() << query.lastError();
             return;
         }
     } else {
         QMessageBox::critical(this, "ERROR", "Query exec error!");
         qDebug() << query.lastError();
         return;
     }
}


void frmMain::on_btnSearchReset_clicked()
{
    ui->cbSearchByName->setChecked(false);
    ui->cbSearchByDate->setChecked(false);
    ui->cbSearchByDateAdd->setChecked(false);
    ui->cbSearchByDateUpdate->setChecked(false);
    ui->cbSearchByQuantity->setChecked(false);
    ui->cbSearchByPrice->setChecked(false);
    ui->cbSearchByPricePurchase->setChecked(false);
    ui->cbSearchByPriceSale->setChecked(false);

    ui->txtSearchByName->clear();
    ui->cbSearchByNamePattern->setCurrentIndex(0);

    ui->dteSearchByDateAddMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateAddMax->setDateTime(QDateTime::currentDateTime());

    ui->dteSearchByDateUpdateMin->setDateTime(QDateTime::currentDateTime());
    ui->dteSearchByDateUpdateMax->setDateTime(QDateTime::currentDateTime());

    ui->sbSearchByQuantity->setValue(0);
    ui->cbSearchByQuantityPattern->setCurrentIndex(0);

    ui->dsbSearchByPricePurchase->setValue(0.0);
    ui->cbSearchByPricePurchasePattern->setCurrentIndex(0);

    ui->dsbSearchByPriceSale->setValue(0.0);
    ui->cbSearchByPriceSalePattern->setCurrentIndex(0);
}

void frmMain::on_btnClear_clicked()
{
    QSqlQueryModel * queryModel = new QSqlQueryModel();
    queryModel->setHeaderData(0, Qt::Horizontal, "ID");
    queryModel->setHeaderData(1, Qt::Horizontal, "Barkod");
    queryModel->setHeaderData(2, Qt::Horizontal, "Ürün");
    queryModel->setHeaderData(3, Qt::Horizontal, "Açıklama");
    queryModel->setHeaderData(4, Qt::Horizontal, "Adet");
    queryModel->setHeaderData(5, Qt::Horizontal, "Alış Fiyatı");
    queryModel->setHeaderData(6, Qt::Horizontal, "Satış Fiyatı");
    queryModel->setHeaderData(7, Qt::Horizontal, "Eklenme Tarihi");
    queryModel->setHeaderData(8, Qt::Horizontal, "Güncelleme Tarihi");
    ui->tblProducts->setModel(queryModel);

}

void frmMain::on_cbSearchByName_stateChanged(int arg1)
{
    ui->txtSearchByName->setEnabled(arg1);
    ui->cbSearchByNamePattern->setEnabled(arg1);
}

void frmMain::on_cbSearchByDate_stateChanged(int arg1)
{
    ui->cbSearchByDateAdd->setEnabled(arg1);
    ui->cbSearchByDateUpdate->setEnabled(arg1);
    if(!arg1){
        ui->dteSearchByDateAddMin->setEnabled(arg1);
        ui->dteSearchByDateAddMax->setEnabled(arg1);

        ui->dteSearchByDateUpdateMin->setEnabled(arg1);
        ui->dteSearchByDateUpdateMax->setEnabled(arg1);
    }else{
        ui->dteSearchByDateAddMin->setEnabled(ui->cbSearchByDateAdd->checkState());
        ui->dteSearchByDateAddMax->setEnabled(ui->cbSearchByDateAdd->checkState());

        ui->dteSearchByDateUpdateMin->setEnabled(ui->cbSearchByDateUpdate->checkState());
        ui->dteSearchByDateUpdateMax->setEnabled(ui->cbSearchByDateUpdate->checkState());
    }
}

void frmMain::on_cbSearchByDateAdd_stateChanged(int arg1)
{
    ui->dteSearchByDateAddMin->setEnabled(arg1);
    ui->dteSearchByDateAddMax->setEnabled(arg1);
}

void frmMain::on_cbSearchByDateUpdate_stateChanged(int arg1)
{
    ui->dteSearchByDateUpdateMin->setEnabled(arg1);
    ui->dteSearchByDateUpdateMax->setEnabled(arg1);
}

void frmMain::on_cbSearchByQuantity_stateChanged(int arg1)
{
    ui->sbSearchByQuantity->setEnabled(arg1);
    ui->cbSearchByQuantityPattern->setEnabled(arg1);
}

void frmMain::on_cbSearchByPrice_stateChanged(int arg1)
{
    ui->cbSearchByPricePurchase->setEnabled(arg1);
    ui->cbSearchByPriceSale->setEnabled(arg1);
    if(!arg1){
        ui->dsbSearchByPricePurchase->setEnabled(arg1);
        ui->cbSearchByPricePurchasePattern->setEnabled(arg1);

        ui->dsbSearchByPriceSale->setEnabled(arg1);
        ui->cbSearchByPriceSalePattern->setEnabled(arg1);
    }else{
        ui->dsbSearchByPricePurchase->setEnabled(ui->cbSearchByPricePurchase->checkState());
        ui->cbSearchByPricePurchasePattern->setEnabled(ui->cbSearchByPricePurchase->checkState());

        ui->dsbSearchByPriceSale->setEnabled(ui->cbSearchByPriceSale->checkState());
        ui->cbSearchByPriceSalePattern->setEnabled(ui->cbSearchByPriceSale->checkState());
    }
}

void frmMain::on_cbSearchByPricePurchase_stateChanged(int arg1)
{
    ui->dsbSearchByPricePurchase->setEnabled(arg1);
    ui->cbSearchByPricePurchasePattern->setEnabled(arg1);
}

void frmMain::on_cbSearchByPriceSale_stateChanged(int arg1)
{
    ui->dsbSearchByPriceSale->setEnabled(arg1);
    ui->cbSearchByPriceSalePattern->setEnabled(arg1);
}
