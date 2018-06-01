// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include "frmProduct.h"
#include "frmLogin.h"
#include <QSqlQueryModel>

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

private:
    frmProduct *m_frmProduct;
    frmLogin *m_frmLogin;

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();
    void LoadProducts();

private slots:

    void loginOKWith(QString name);

    void showMenuAbout();

    void quitApp();

    void on_btnRefresh_clicked();

    void on_btnProductOperations_clicked();

    void on_tblProducts_activated(const QModelIndex &index);

    void on_tblProducts_pressed(const QModelIndex &index);

    void on_btnSearch_clicked();

    void on_btnSearchReset_clicked();

    void on_btnClear_clicked();

    void on_cbSearchByName_stateChanged(int arg1);

    void on_cbSearchByDate_stateChanged(int arg1);

    void on_cbSearchByQuantity_stateChanged(int arg1);

    void on_cbSearchByPrice_stateChanged(int arg1);

    void on_cbSearchByDateAdd_stateChanged(int arg1);

    void on_cbSearchByDateUpdate_stateChanged(int arg1);

    void on_cbSearchByPricePurchase_stateChanged(int arg1);

    void on_cbSearchByPriceSale_stateChanged(int arg1);

private:
    Ui::frmMain *ui;
    void LoadProductInfoToLabel(const QModelIndex &index);
    void closeEvent (QCloseEvent *event);

};

#endif // FRMMAIN_H
