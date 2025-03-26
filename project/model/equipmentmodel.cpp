#include "equipmentmodel.h"
#include "util/sqliteutil.h"
#include <QString>
//#include "util/simpleQtLogger.h"

EquipmentModel::EquipmentModel()
{

}

int EquipmentModel::queryAllEquipmentNumber(char **&result, int &row, int &col)
{
    QString sql = QString("SELECT tbl_equipment.equipment_number FROM tbl_equipment;");
    int res = SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    if(res != SQLITE_OK)
    {
//        L_INFO("query allEquipmentNumber is error");
    }
    return res;
}
