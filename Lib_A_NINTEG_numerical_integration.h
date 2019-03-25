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

#if defined (__GNUC__)

	/* inline*/
	#ifndef __NINTEG_INLINE
		#define __NINTEG_INLINE         inline
	#endif

	/* static inline */
	#ifndef __NINTEG_STATIC_INLINE
		#define __NINTEG_STATIC_INLINE  static inline
	#endif

	/* always inline */
	#ifndef __NINTEG_ALWAYS_INLINE
		#define __NINTEG_ALWAYS_INLINE 	inline __attribute__((always_inline)) static
	#endif

#else
	#define __NINTEG_INLINE
	#define __NINTEG_STATIC_INLINE   	static
	#define __NINTEG_ALWAYS_INLINE
#endif
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
__NINTEG_ALWAYS_INLINE __NINTEG_FPT__
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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      25-мар-2019
 *
 * @brief    Функция выполняет численное интегрирование методом трапеций
 *           за промежуток времени "dT"
 *
 * @param[in,out]   *pTrapz_s:  Указатель на структуру, в которой содержатся
 * 								данные для выполнения численного интегрирования
 * 								методом трапеций
 * @param[in]    	newData: 	Новое значение величины, интегрирование которой
 *  							необходимо выполнить
 *
 * @return 		Если (pTrapz_s->tumblers_s.accumEn == NINTEG_ENABLE), то функция возвращает аккумулированное значение интеграла
 *              Если (pTrapz_s->tumblers_s.accumEn != NINTEG_ENABLE), то функция возвращает приращение интеграла
 */
__NINTEG_ALWAYS_INLINE __NINTEG_FPT__
NINTEG_Trapz(
	ninteg_trapz_s *pTrapz_s,
	__NINTEG_FPT__ newData)
{
	/* Численное интегрирование методом трапеций */
	pTrapz_s->deltaData =
		(pTrapz_s->previousData + newData) * pTrapz_s->dT * (__NINTEG_FPT__) 0.5;

	/* Копирование текущего значения переменной в переменную данных за предыдущий момент времени */
	pTrapz_s->previousData = newData;

	/* Если разрешено аккумулирование методом трапеций */
	if (pTrapz_s->tumblers_s.accumEn == NINTEG_ENABLE)
	{
		/* Инкремент аккумулятора */
		pTrapz_s->accumData += pTrapz_s->deltaData;

		/* Ограничение насыщения */
		pTrapz_s->accumData =
			RestrictionSaturation(
				pTrapz_s->accumData,
				pTrapz_s->accumDataSaturation);

		/* Возврат аккумулированного значения */
		return (pTrapz_s->accumData);
	}
	else
	{
		/* Возврат дельты за промежуток времени */
		return (pTrapz_s->deltaData);
	}
}
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif	/* LIB_A_NINTEG_NUMERICAL_INTEGRATION_H */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
