// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#pragma once

#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>

class DBController : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase m_db;
    DBController(QObject* parent = 0);
    static DBController* createInstance();
public:
    ~DBController();
    void SetupDB();
    bool IsOpen();
    bool Connect();
    void Disconnect();
    QString GetError();
    QSqlDatabase GetDB();

    static DBController* instance();
};

#endif
