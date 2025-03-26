#ifndef POLICECONTROLLER_H
#define POLICECONTROLLER_H

#include "model/policemodel.h"

class PoliceController
{
public:
    PoliceController();
    int loginService(QString number, QString pwd);
};

#endif // POLICECONTROLLER_H
