// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#ifndef FRMREGISTER_H
#define FRMREGISTER_H

#include <QDialog>

namespace Ui {
class frmRegister;
}

class frmRegister : public QDialog
{
    Q_OBJECT

private:
    void Clear();
    bool CheckInputs();

public:
    explicit frmRegister(QWidget *parent = 0);
    ~frmRegister();

private slots:
    void on_btnRegister_clicked();

private:
    Ui::frmRegister *ui;
};

#endif // FRMREGISTER_H
