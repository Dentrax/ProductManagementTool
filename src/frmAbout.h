// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QDialog>

namespace Ui {
class frmAbout;
}

class frmAbout : public QDialog
{
    Q_OBJECT

public:
    explicit frmAbout(QWidget *parent = 0);
    ~frmAbout();

private slots:
    void on_btnOK_clicked();

private:
    Ui::frmAbout *ui;
};

#endif // FRMABOUT_H
