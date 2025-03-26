#ifndef EQUIPMENTCONTROLLER_H
#define EQUIPMENTCONTROLLER_H

#include "data/equipment.h"
#include <QList>
#include <QString>

class EquipmentController
{
public:
    EquipmentController();
    QList<QString> getAllEquipmentNumber();
};

#endif // EQUIPMENTCONTROLLER_H
