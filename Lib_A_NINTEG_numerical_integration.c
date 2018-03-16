/**
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: %<%USER%>%
 *
 * Created on %<%DATE%>%, %<%TIME%>%
 */

/******************************************************************************/
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_A_NINTEG_numerical_integration.h"
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
void NINTEG_IntegrateAngleVelocityTrapeziumAllAxis(
                                                   float *pPreviousAngleVelocityArr,
                                                   float *pCurrentAngleVelocityArr,
                                                   float deltaTimeInSec,
                                                   float *pDeltaAnglesArr)
{
    //  Нахождение дельты угла по оси X;
    *pDeltaAnglesArr++ = NINTEG_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr++, \
                          pCurrentAngleVelocityArr++, \
                          deltaTimeInSec);

    //  Нахождение дельты угла по оси Y;
    *pDeltaAnglesArr++ = NINTEG_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr++, \
                          pCurrentAngleVelocityArr++, \
                          deltaTimeInSec);

    //  Нахождение дельты угла по оси Z;
    *pDeltaAnglesArr = NINTEG_IntegrateAnglVelocityTrapezium \
                         (pPreviousAngleVelocityArr, \
                          pCurrentAngleVelocityArr, \
                          deltaTimeInSec);
}

float NINTEG_IntegrateAnglVelocityTrapezium(
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

/**
 * @brief   Функция находит приращение величины методом трапеций за промежуток
 *          времени "dT";
 * @param   *pStruc^:   Указатель на структуру, содержащую данные для нахождения
 *                      приращения величины за промежуток времени;
 * @param   newData:    Новое значение для нахождения приращения;
 * @return  Приращение величины за промежуток времени;
 */
float NINTEG_FindDeltaTrapezium(
                                NINTEG_find_delta_trapezium_s *pStruct,
                                float newData)
{
    // Численное интегрирование методом трапеций;
    pStruct->deltaData = (pStruct->previousData + newData) * pStruct->dT / 2.0f;

    // Копирование текущего значения переменной в переменную данных за предыдущий момент времени;
    pStruct->previousData = newData;

    // Возврат интегрированного значения;
    return pStruct->deltaData;
}

void NINTEG_InitIntegrateTrapeziumStruct(
                                    NINTEG_find_delta_trapezium_s *pStruct,
                                    float dT)
{
    pStruct->dT = dT;
    pStruct->deltaData = 0.0f;
    pStruct->previousData = 0.0f;
}
/*============================================================================*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
