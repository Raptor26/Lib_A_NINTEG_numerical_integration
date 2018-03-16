/**
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: %<%USER%>%
 *
 * Created on %<%DATE%>%, %<%TIME%>%
 */

/******************************************************************************/
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_A_AVI_angular_velocity_integrate.h"
/******************************************************************************/


/******************************************************************************/
/*============================================================================*/
// Глобальные переменные
/*============================================================================*/


/*============================================================================*/
// Локальные переменные
/*============================================================================*/
/******************************************************************************/


/******************************************************************************/
// Секция прототипов локальных функций
/******************************************************************************/


/******************************************************************************/
// Секция описания функций (сначала глобальных, потом локальных)

/*============================================================================*/
void AVI_IntegrateAngleVelocityTrapeziumAllAxis(
                                                float *pPreviousAngleVelocityArr,
                                                float *pCurrentAngleVelocityArr,
                                                float deltaTimeInSec,
                                                float *pDeltaAnglesArr)
{
    //  Нахождение дельты угла по оси X;
    *pDeltaAnglesArr++ = AVI_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr++, \
                          pCurrentAngleVelocityArr++, \
                          deltaTimeInSec);

    //  Нахождение дельты угла по оси Y;
    *pDeltaAnglesArr++ = AVI_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr++, \
                          pCurrentAngleVelocityArr++, \
                          deltaTimeInSec);

    //  Нахождение дельты угла по оси Z;
    *pDeltaAnglesArr = AVI_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr, \
                          pCurrentAngleVelocityArr, \
                          deltaTimeInSec);
}

float AVI_IntegrateAnglVelocityTrapezium(
                                         float *pPreviousAngleVelocity,
                                         float *pCurrentAngleVelocity,
                                         float deltaTimeInSec)
{
    //  Нахождение угла на основе текущей угловой скорости и угловой скорости в
    //  предыдущий момент времени;
    float deltaAngel = (*pPreviousAngleVelocity + *pCurrentAngleVelocity) * deltaTimeInSec / 2.0f;

    //  Копирование текущей угловой скорости в переменную угловой скорости за
    //  предыдущий момент времени;
    *pPreviousAngleVelocity = *pCurrentAngleVelocity;

    return deltaAngel;
}

float AVI_IntegrateTrapezium(
                             AVI_trapezium_integrate_s *pStruct,
                             float data)
{
    // Численное интегрирование методом трапеций;
    pStruct->integratedata = (pStruct->previousData + data) * pStruct->dT / 2.0f;

    // Копирование текущего значения переменной в переменную данных за предыдущий момент времени;
    pStruct->previousData = data;

    // Возврат интегрированного значения;
    return pStruct->integratedata;
}
/*============================================================================*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
