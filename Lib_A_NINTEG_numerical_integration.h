/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


#ifndef LIB_A_NINTEG_NUMERICAL_INTEGRATION_H
#define LIB_A_NINTEG_NUMERICAL_INTEGRATION_H


/*#### |Begin| --> Секция - "Include" ########################################*/
/*==== |Begin| --> Секция - "C libraries" ====================================*/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*==== |End  | <-- Секция - "C libraries" ====================================*/

/*==== |Begin| --> Секция - "MK peripheral libraries" ========================*/
/*==== |End  | <-- Секция - "MK peripheral libraries" ========================*/

/*==== |Begin| --> Секция - "Extern libraries" ===============================*/
#if defined (__NINTEG_EXTERN_MODE_ENABLE__)
	#include "macros_definitions.h"
#endif
/*==== |End  | <-- Секция - "Extern libraries" ===============================*/
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Определение констант" ###########################*/
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

/*==== |Begin| --> Секция - Макросы для встраиваемых функций =================*/
#if defined (__GNUC__)

	/* inline*/
	#ifndef __NINTEG_INLINE
		#define __NINTEG_INLINE          inline
	#endif

	/* static inline */
	#ifndef __NINTEG_STATIC_INLINE
		#define __NINTEG_STATIC_INLINE   static inline
	#endif

	/* always inline */
	#ifndef __NINTEG_ALWAYS_INLINE
		#define __NINTEG_ALWAYS_INLINE    inline __attribute__((always_inline)) static
	#endif

	/* force inline */
	#ifndef __NINTEG_FORCE_INLINE
		#define __NINTEG_FORCE_INLINE    inline __attribute__((always_inline))
	#endif

#else
	#define __NINTEG_INLINE
	#define __NINTEG_STATIC_INLINE   static
	#define __NINTEG_ALWAYS_INLINE
#endif
/*==== |End  | <-- Секция - Макросы для встраиваемых функций =================*/


/*==== |Begin| --> Секция - Расположение функций библиотеки в специальной
 *                          области памяти ===================================*/
#if defined (__NINTEG_FNC_ONCE_MEMORY_LOCATION_NAME__)
	#if defined (__GNUC__)
		#define __NINTEG_FNC_ONCE_MEMORY_LOCATION  __attribute__ ((section(__NINTEG_FNC_ONCE_MEMORY_LOCATION_NAME__)))
	#else
		#error "You defined the name of the memory area for the function location, but the type of your compiler is not supported by the library. You can delete the macro definition __NINTEG_FNC_ONCE_MEMORY_LOCATION_NAME__ or extend the macro definition __NINTEG_FNC_ONCE_MEMORY_LOCATION for your compiler type"
	#endif
#else
	#define __NINTEG_FNC_ONCE_MEMORY_LOCATION
#endif

#if defined (__NINTEG_FNC_LOOP_MEMORY_LOCATION_NAME__)
	#if defined (__GNUC__)
		#define __NINTEG_FNC_LOOP_MEMORY_LOCATION  __attribute__ ((section(__NINTEG_FNC_LOOP_MEMORY_LOCATION_NAME__)))
	#else
		#error "You defined the name of the memory area for the function location, but the type of your compiler is not supported by the library. You can delete the macro definition __NINTEG_FNC_LOOP_MEMORY_LOCATION_NAME__ or extend the macro definition __NINTEG_FNC_LOOP_MEMORY_LOCATION for your compiler type"
	#endif
#else
	#define __NINTEG_FNC_LOOP_MEMORY_LOCATION
#endif
/*==== |End  | <-- Секция - Расположение функций библиотеки в специальной
 *                          области памяти ===================================*/

/*==== |Begin| --> Секция - Локальная оптимизация функций ====================*/
#if defined (__GNUC__)
	#ifndef __NINTEG_FNC_ONCE_OPTIMIZE_MODE
		#define __NINTEG_FNC_ONCE_OPTIMIZE_MODE
	#endif
#endif

#if defined (__GNUC__)
	#ifndef __NINTEG_FNC_LOOP_OPTIMIZE_MODE
		#define __NINTEG_FNC_LOOP_OPTIMIZE_MODE
	#endif
#endif
/*==== |End| --> Секция - Локальная оптимизация функций ======================*/
/*#### |End  | <-- Секция - "Определение констант" ###########################*/


/*#### |Begin| --> Секция - "Определение типов" ##############################*/
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
} ninteg_trapz_init_s;
/*#### |End  | <-- Секция - "Определение типов" ##############################*/


/*#### |Begin| --> Секция - "Определение глобальных переменных" ##############*/
/*#### |End  | <-- Секция - "Определение глобальных переменных" ##############*/


/*#### |Begin| --> Секция - "Прототипы глобальных функций" ###################*/
extern void
NINTEG_Trapz_StructInit(
	ninteg_trapz_init_s *pInitStruct);

extern ninteg_fnc_status_e
NINTEG_Trapz_Init(
	ninteg_trapz_s			*pTrapzStruct,
	ninteg_trapz_init_s 	*pInitStruct);


/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      25-мар-2019
 *
 * @brief    Функция задает ограничение насыщения переменной
 *
 * @param[in]    value:         Переменная, насыщение которой необходимо ограничить
 * @param[in]    saturation:    Значение насыщения
 *
 * @return    параметр "value" с учетом насыщения, заданного параметром "saturation"
 */
__NINTEG_ALWAYS_INLINE __NINTEG_FPT__ __NINTEG_FNC_LOOP_OPTIMIZE_MODE
RestrictionSaturation (
	__NINTEG_FPT__ value,
	__NINTEG_FPT__ saturation)
{
	/*    Ограничение насыщения выходного параметра */
	if (saturation != (__NINTEG_FPT__) 0.0)
	{
		/* Если выходное значение больше положительного значения переменной насыщения */
		if (value > saturation)
		{
			value = saturation;
		}
		/* Если выходное значение меньше отрицательного значения переменной насыщения */
		else if (value < (-saturation))
		{
			value = -saturation;
		}
	}
	return (value);
}

extern __NINTEG_FPT__ __NINTEG_FNC_LOOP_OPTIMIZE_MODE
NINTEG_Trapz(
	ninteg_trapz_s *pTrapz_s,
	__NINTEG_FPT__ newData
) __NINTEG_FNC_LOOP_MEMORY_LOCATION;
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif	/* LIB_A_NINTEG_NUMERICAL_INTEGRATION_H */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
