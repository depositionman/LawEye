#include "equipmentcontroller.h"
#include "model/equipmentmodel.h"
#include "util/sqliteutil.h"
#include <QDebug>
//#include "util/simpleQtLogger.h"

EquipmentController::EquipmentController()
{

}

QList<QString> EquipmentController::getAllEquipmentNumber()
{
    QList<QString> equipmenNumbertList;
    EquipmentModel equipmentModel;
    char **result = nullptr;
    int row = 0;
    int col = 0;
    int res = equipmentModel.queryAllEquipmentNumber(result, row, col);
    if(res == SQLITE_OK)
    {
        for(int i = 1; i <= row; ++i)
        {
            equipmenNumbertList.append(result[i*col]);
        }
//        L_INFO("gain allEquipmentNumber is success");
    }
    return equipmenNumbertList;
}
