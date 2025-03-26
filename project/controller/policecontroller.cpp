#include "policecontroller.h"

PoliceController::PoliceController()
{

}

int PoliceController::loginService(QString number, QString pwd)
{
    PoliceModel policeModel;
    return policeModel.queryPoliceByNumberPwd(number,pwd);
}
