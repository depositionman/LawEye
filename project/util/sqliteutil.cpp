#include "sqliteutil.h"
#include <QDebug>

SqliteUtil* SqliteUtil::sqliteUtil = nullptr;

SqliteUtil::SqliteUtil()
{
    this->pdb = nullptr;
    //连接数据库
    int res = sqlite3_open("bodyWornCamera.db" ,&this->pdb);
    if(res != SQLITE_OK){
        qDebug() << "数据库打开失败";
        qDebug() << sqlite3_errmsg(this->pdb);
        qDebug() << sqlite3_errcode(this->pdb);
    }
}

SqliteUtil *SqliteUtil::getSqliteUtil()
{
    if(SqliteUtil::sqliteUtil == nullptr){
        SqliteUtil::sqliteUtil = new SqliteUtil();
    }
    return SqliteUtil::sqliteUtil;
}

int SqliteUtil::updateSqlite(QString sql)
{
    char *errmsg = nullptr;
    int res = sqlite3_exec(this->pdb, sql.toUtf8(), nullptr, nullptr, &errmsg);
    if(res != SQLITE_OK){
        qDebug() << "数据更新失败";
        qDebug() << sqlite3_errmsg(this->pdb);
        qDebug() << sqlite3_errcode(this->pdb);
    }
    return res;
}

int SqliteUtil::querySqlite(QString sql, char **&result, int &row, int &col)
{
    char *errmsg = nullptr;
    int res = sqlite3_get_table(this->pdb, sql.toUtf8(), &result, &row, &col, &errmsg);
    if(res != SQLITE_OK){
        qDebug() << "查询失败";
        qDebug() << sqlite3_errmsg(this->pdb);
        qDebug() << sqlite3_errcode(this->pdb);
    }
    return res;
}
