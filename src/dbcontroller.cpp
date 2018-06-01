// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include "dbcontroller.h"
#include <QObject>
#include "singleton.h"
#include <QSqlDatabase>
#include <QSqlError>

DBController::DBController(QObject* parent): QObject(parent){

}

DBController* DBController::createInstance()
{
    return new DBController();
}

DBController::~DBController()
{
}

DBController* DBController::instance()
{
    return Singleton<DBController>::instance(DBController::createInstance);
}

void DBController::SetupDB(){
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setDatabaseName("pmt");
    m_db.setUserName("root");
    m_db.setPassword("1234");
}

bool DBController::IsOpen(){
    return m_db.isOpen();
}

bool DBController::Connect(){
    return m_db.open();
}

void DBController::Disconnect(){
    m_db.close();
}

QString DBController::GetError(){
    return m_db.lastError().text();
}

QSqlDatabase DBController::GetDB(){
    return m_db;
}
