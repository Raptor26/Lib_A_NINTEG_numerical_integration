/**
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: %<%USER%>%
 *
 * Created on %<%DATE%>%, %<%TIME%>%
 */

#ifndef LIB_A_NINTEG_NUMERICAL_INTEGRATION_H
#define LIB_A_NINTEG_NUMERICAL_INTEGRATION_H

/******************************************************************************/
//  Секция include (подключаем заголовочные файлы используемых модулей)
/*============================================================================*/
//  Стандартные библиотеки языка С
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*============================================================================*/


/*============================================================================*/
//  Библиотеки для работы с периферией микроконтроллера
/*============================================================================*/


/*============================================================================*/
//  Внешние модули
/*============================================================================*/
/******************************************************************************/


/******************************************************************************/
//  Секция определения констант
/******************************************************************************/


/******************************************************************************/
//  Секция определения типов

typedef struct {
	float anglVelocity;
	float dT;
	size_t integrateTacktFlag;
} NINTEG_data_for_integrate_s;

/**
 * @brief   Структура, содержащая поля для нахождения дельты между измерениями
 *          методом трапеций;
 */
typedef struct {
	/**
	 * @brief   Значение приращения угла на момент завершения работы
	 *          функции NINTEG_FindDeltaTrapezium();
	 * @note    Выходное значение фукнции NINTEG_FindDeltaTrapezium();
	 */
	float deltaData;

	/**
	 * @brief   Период в секундах между измерениями;
	 */
	float dT;

	/**
	 * @brief   Измерения, которые были получены в предыдущем
	 *          вызове функции NINTEG_FindDeltaTrapezium();
	 */
	float previousData;
} NINTEG_find_delta_trapezium_s;
/******************************************************************************/


/******************************************************************************/
//  Секция определения глобальных переменных
/******************************************************************************/


/******************************************************************************/
//  Секция прототипов глобальных функций
extern float
NINTEG_IntegrateAnglVelocityTrapezium(
  float *pPreviousAngleVelocity,
  float *pCurrentAngleVelocity,
  float deltaTimeInSec);

extern void
NINTEG_IntegrateAngleVelocityTrapeziumAllAxis(
  float *pPreviousAngleVelocityArr,
  float *pCurrentAngleVelocityArr,
  float deltaTimeInSec,
  float *pDeltaAngelsArr);

extern float
NINTEG_FindDeltaTrapezium(
  NINTEG_find_delta_trapezium_s *pStruct,
  float data);

extern void
NINTEG_InitIntegrateTrapeziumStruct(
  NINTEG_find_delta_trapezium_s *pStruct,
  float dT);
/******************************************************************************/


/******************************************************************************/
//  Секция определения макросов
/******************************************************************************/

#endif  /* LIB_A_NINTEG_NUMERICAL_INTEGRATION_H */

////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////