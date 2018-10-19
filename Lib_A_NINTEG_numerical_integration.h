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
#if !defined (__NUNTEG_FPT__)
#error 'Please, define __NUNTEG_FPT__, default value is float or double'
#endif


typedef enum
{
	NINTEG_DISABLE = 0,
	NINTEG_ENABLE,
} ninteg_tumblers_status_e;

typedef enum
{
	NINTEG_ERROR = 0,
	NINTEG_SUCCESS,
} ninteg_fnc_status_e;

typedef struct {
	__NUNTEG_FPT__ anglVelocity;
	__NUNTEG_FPT__ dT;
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
	 * @note    Выходное значение функции NINTEG_FindDeltaTrapezium();
	 */
	__NUNTEG_FPT__ deltaData;

	/**
	 * @brief   Период в секундах между измерениями;
	 */
	__NUNTEG_FPT__ dT;

	/**
	 * @brief   Измерения, которые были получены в предыдущем
	 *          вызове функции NINTEG_FindDeltaTrapezium();
	 */
	__NUNTEG_FPT__ previousData;

	/**
	 * @brief Аккумулятор интегрирования
	 */
	__NUNTEG_FPT__ accumData;

	/**
	 * @brief Значение насыщения аккумулированных данных
	 */
	__NUNTEG_FPT__ accumDataSaturation;

	struct
	{
		ninteg_tumblers_status_e accumEn;
	} tumblers_s;
} ninteg_trapz_s;

typedef struct
{
	__NUNTEG_FPT__ integratePeriod;						/*!< 	Период интегрирования в секундах */

	__NUNTEG_FPT__ accumDataSaturation;

	ninteg_tumblers_status_e accumulate_flag;	/*!<	Включение аккумулирования выходной величины.
														Может иметь одно из следующих значений:
														@arg @ref NINTEG_ENABLE
														@arg @ref NINTEG_DISABLE */
} ninteg_trapz_init_struct_s;
/******************************************************************************/


/******************************************************************************/
//  Секция определения глобальных переменных
/******************************************************************************/


/******************************************************************************/
//  Секция прототипов глобальных функций
extern __NUNTEG_FPT__
NINTEG_IntegrateAnglVelocityTrapezium(
	__NUNTEG_FPT__ *pPreviousAngleVelocity,
	__NUNTEG_FPT__ *pCurrentAngleVelocity,
	__NUNTEG_FPT__ deltaTimeInSec);

extern void
NINTEG_IntegrateAngleVelocityTrapeziumAllAxis(
	__NUNTEG_FPT__ *pPreviousAngleVelocityArr,
	__NUNTEG_FPT__ *pCurrentAngleVelocityArr,
	__NUNTEG_FPT__ deltaTimeInSec,
	__NUNTEG_FPT__ *pDeltaAngelsArr);

extern __NUNTEG_FPT__
NINTEG_Trapz(
	ninteg_trapz_s *pStruct,
	__NUNTEG_FPT__ data);

extern void
NINTEG_Trapz_StructInit(
	ninteg_trapz_init_struct_s *pInitStruct);

extern ninteg_fnc_status_e
NINTEG_Trapz_Init(
	ninteg_trapz_s			 	*p_s,
	ninteg_trapz_init_struct_s 	*pInitStruct);
/******************************************************************************/


/******************************************************************************/
//  Секция определения макросов
/******************************************************************************/

#endif  /* LIB_A_NINTEG_NUMERICAL_INTEGRATION_H */

////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
