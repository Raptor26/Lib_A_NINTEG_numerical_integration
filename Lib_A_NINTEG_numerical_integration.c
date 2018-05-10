/**
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: %<%USER%>%
 *
 * #############################################################################
 * ########## <Функции, используемые в данном программном модуле> ##############
 * #############################################################################
 * @note    В Данной библиотеки находятся следующие функции:
 *          --------------------------------------------------------------------
 *          --  NINTEG_FindDeltaTrapezium() - функция, для нахождения приращения
 *              величины методом трапеций за промежуток времени "dT";
 *          --  NINTEG_InitFindDeltaTrapeziumStruct() - функция, инициализирующая
 *              структуру, необходимую для функции NINTEG_FindDeltaTrapezium();
 *      @code
 *          ...
 *          // Объявление перменных;
 *          NINTEG_find_delta_trapezium_s   gyrDeltaAngleX,
 *                                          gyrDeltaAngleY,
 *                                          gyrDeltaAngleZ;
 *          float   deltaAngleX,
 *                  deltaAngleY,
 *                  deltaAngleZ;
 *          // Период интегрирования в сек;
 *          float dT = 0.001f;
 *          ...
 *          int main(void)
 *          {
 *              ...
 *              // Инициализация структур;
 *              NINTEG_InitFindDeltaTrapeziumStruct(&gyrDeltaAngleX, dT);
 *              NINTEG_InitFindDeltaTrapeziumStruct(&gyrDeltaAngleY, dT);
 *              NINTEG_InitFindDeltaTrapeziumStruct(&gyrDeltaAngleZ, dT);
 *              ...
 *              while(1)
 *              {
 *                  ...
 *                  deltaAngleX = NINTEG_FindDeltaTrapezium(&gyrDeltaAngleX,
 *                                                          newAngleSpeedX);
 *                  deltaAngleY = NINTEG_FindDeltaTrapezium(&gyrDeltaAngleY,
 *                                                          newAngleSpeedY);
 *                  deltaAngleZ = NINTEG_FindDeltaTrapezium(&gyrDeltaAngleZ,
 *                                                          newAngleSpeedZ);
 *
 *                  // Причем:
 *                  deltaAngleX == gyrDeltaAngleX.deltaData;
 *                  deltaAngleY == gyrDeltaAngleY.deltaData;
 *                  deltaAngleZ == gyrDeltaAngleZ.deltaData;
 *                  ...
 *              }
 *              return 0;
 *          }
 *      @endcode
 *      ------------------------------------------------------------------------
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
	*pDeltaAnglesArr++ = NINTEG_IntegrateAnglVelocityTrapezium
	                     (
	                     pPreviousAngleVelocityArr++,
	                     pCurrentAngleVelocityArr++,
	                     deltaTimeInSec);

	//  Нахождение дельты угла по оси Y;
	*pDeltaAnglesArr++ = NINTEG_IntegrateAnglVelocityTrapezium
	                     (
	                     pPreviousAngleVelocityArr++,
	                     pCurrentAngleVelocityArr++,
	                     deltaTimeInSec);

	//  Нахождение дельты угла по оси Z;
	*pDeltaAnglesArr = NINTEG_IntegrateAnglVelocityTrapezium
	                   (
	                   pPreviousAngleVelocityArr,
	                   pCurrentAngleVelocityArr,
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
 *          времени "dT".
 *          dT = время между вызовами функции NINTEG_FindDeltaTrapezium();
 * @param   *pStruct:   Указатель на структуру, содержащую данные для нахождения
 *                      приращения величины за промежуток времени;
 * @param   newData:    Новое значение для нахождения приращения;
 * @return  Приращение величины за промежуток времени "dT".
 *      @note   (Приращение за промежуток времени между вызовами функии
 *              "NINTEG_FindDeltaTrapezium()");
 */
float NINTEG_FindDeltaTrapezium
(NINTEG_find_delta_trapezium_s *pStruct,
    float newData)
{
	// Численное интегрирование методом трапеций;
	pStruct->deltaData
	= (pStruct
	   ->previousData + newData) * pStruct->dT / 2.0f;
	
	// Копирование текущего значения переменной в переменную данных за предыдущий момент времени;
	pStruct
	->previousData = newData;

	// Возврат интегрированного значения;
	return pStruct->deltaData;
}

/**
 * @brief   Функция инициализирует структуру типа NINTEG_find_delta_trapezium_s;
 * @param   *pStruct:   Указатель на структуру, в которой содержатся данные для
 *                      нахождения дельты величины между вызовами функции
 *                      NINTEG_FindDeltaTrapezium();
 * @param   dT: Период времени в секундах, для нахождения приращения величины;
 * @return  None;
 */
void NINTEG_InitFindDeltaTrapeziumStruct(
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
