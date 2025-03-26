#ifndef POLICEMODEL_H
#define POLICEMODEL_H

#include "data/police.h"

#define EXIST 2
#define NOTEXIST 3

class PoliceModel
{
public:
    PoliceModel();
    int queryPoliceByNumberPwd(QString number, QString pwd);
};

#endif // POLICEMODEL_H
