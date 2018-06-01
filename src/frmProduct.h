// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#ifndef FRMPRODUCT_H
#define FRMPRODUCT_H

#include <QDialog>

namespace Ui {
class frmProduct;
}

class frmProduct : public QDialog
{
    Q_OBJECT

public:
    explicit frmProduct(QWidget *parent = 0);
    ~frmProduct();

    void Clear();
    void LoadProduct(const int index);


private:
    bool m_isReadonly;

    bool CheckInputs();
    void LoadProduct(const QString barcode);
    void LoadProductsToComboBox();

signals:
    void Refresh();


public slots:

    void on_btnAdd_clicked();

    void on_btnUpdate_clicked();

    void on_btnDelete_clicked();

    void on_cbID_activated(int index);

    void on_cbReadonly_stateChanged(int arg1);

private:
    Ui::frmProduct *ui;
};

#endif // FRMPRODUCT_H
