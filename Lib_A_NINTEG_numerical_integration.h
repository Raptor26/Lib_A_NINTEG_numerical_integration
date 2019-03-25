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

/* |Begin| --> Секция определения типа числа с плавающей точкой ============= */
#if !defined (__NINTEG_FPT__)
#error "Please, set __NINTEG_FPT__ float or double in macros list"
#endif

#if !defined (__NINTEG_FPT_SIZE__)
#error "Please, set __NINTEG_FPT_SIZE__ 4 (that mean float) or 8 (that mean double) in macros list"
#endif

#if     __NINTEG_FPT_SIZE__ == 4

#elif   __NINTEG_FPT_SIZE__ == 8

#else
#error "Your compiler uses a non-standard floating point size"
#endif
/* |End  | <-- Секция определения типа числа с плавающей точкой ============= */


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
	__NINTEG_FPT__ anglVelocity;
	__NINTEG_FPT__ dT;
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
	__NINTEG_FPT__ deltaData;

	/**
	 * @brief   Период в секундах между измерениями;
	 */
	__NINTEG_FPT__ dT;

	/**
	 * @brief   Измерения, которые были получены в предыдущем
	 *          вызове функции NINTEG_FindDeltaTrapezium();
	 */
	__NINTEG_FPT__ previousData;

	/**
	 * @brief 	Аккумулятор интегрирования
	 */
	__NINTEG_FPT__ accumData;

	/**
	 * @brief 	Значение насыщения аккумулированных данных
	 */
	__NINTEG_FPT__ accumDataSaturation;

	/**
	 * @brief 	Статус инициализации структуры
	 */
	ninteg_fnc_status_e initStatus_e;

	struct
	{
		ninteg_tumblers_status_e accumEn;
	} tumblers_s;
} ninteg_trapz_s;

typedef struct
{
	__NINTEG_FPT__ integratePeriod;				/*!< Период интегрирования в секундах */

	__NINTEG_FPT__ accumDataSaturation;			/*!< Значение насыщения аккумулированного значения */

	ninteg_tumblers_status_e accumulate_flag;	/*!< Включение аккумулирования выходной величины.
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
extern __NINTEG_FPT__
NINTEG_IntegrateAnglVelocityTrapezium(
	__NINTEG_FPT__ *pPreviousAngleVelocity,
	__NINTEG_FPT__ *pCurrentAngleVelocity,
	__NINTEG_FPT__ deltaTimeInSec);

extern void
NINTEG_IntegrateAngleVelocityTrapeziumAllAxis(
	__NINTEG_FPT__ *pPreviousAngleVelocityArr,
	__NINTEG_FPT__ *pCurrentAngleVelocityArr,
	__NINTEG_FPT__ deltaTimeInSec,
	__NINTEG_FPT__ *pDeltaAngelsArr);

extern __NINTEG_FPT__
NINTEG_Trapz(
	ninteg_trapz_s *pStruct,
	__NINTEG_FPT__ data);

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
