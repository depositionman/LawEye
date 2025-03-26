#ifndef SQLITEUTIL_H
#define SQLITEUTIL_H

#include "sqlite3.h"
#include <QString>

class SqliteUtil
{
private:
    sqlite3 *pdb;//创建数据库类型的指针
    //1.私有化构造方法
    SqliteUtil();//空参构造
    //2.提供一个私有化的静态变量指针
    static SqliteUtil* sqliteUtil;
public:
    //3.给予一个接口来调用对象
    static SqliteUtil* getSqliteUtil();
    //更新数据库
    int updateSqlite(QString sql);
    //查看数据库
    int querySqlite(QString sql, char **&result, int &row, int &col);
};

#endif // SQLITEUTIL_H
