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

typedef enum
{
	NINTEG_ENABLE = 0,
	NINTEG_DISABLE = 1,
}ninteg_tumblers_status_e;

typedef enum
{
	NINTEG_ERROR = 0,
	NINTEG_SUCCESS,
}ninteg_fnc_status_e;

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

    /**
     * @brief Аккумулятор интегрирования
     */
	float accumData;

	struct
	{
		ninteg_tumblers_status_e accumEn;
	} tumblers_s;
} ninteg_trapz_s;

typedef struct
{
	float integratePeriod;						/*!< 	Период интегрирования в секундах */

	ninteg_tumblers_status_e accumulate_flag;	/*!<	Включение аккумулирования выходной величины.
														Может иметь одно из следующих значений:
														@arg @ref NINTEG_ENABLE
														@arg @ref NINTEG_DISABLE */
} ninteg_trapz_InitStruct_s;
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
NINTEG_Trapz(
	ninteg_trapz_s *pStruct,
	float data);

extern void
NINTEG_InitStruct_Trapz(
	ninteg_trapz_s *pStruct,
	float dT);

extern ninteg_fnc_status_e
NINTEG_Trapz_Init(
	ninteg_trapz_s			 	*p_s,
	ninteg_trapz_InitStruct_s 	*pInitStruct);
/******************************************************************************/


/******************************************************************************/
//  Секция определения макросов
/******************************************************************************/

#endif  /* LIB_A_NINTEG_NUMERICAL_INTEGRATION_H */

////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
