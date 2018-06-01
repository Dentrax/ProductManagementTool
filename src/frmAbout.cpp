// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "frmAbout.h"
#include "ui_frmAbout.h"

frmAbout::frmAbout(QWidget *parent) : QDialog(parent), ui(new Ui::frmAbout){
    ui->setupUi(this);

    this->setFixedSize(this->maximumSize());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

frmAbout::~frmAbout()
{
    delete ui;
}

void frmAbout::on_btnOK_clicked()
{
    this->close();
}
