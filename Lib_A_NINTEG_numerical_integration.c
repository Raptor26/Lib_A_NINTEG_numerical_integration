/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_NINTEG_numerical_integration.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
void
NINTEG_Trapz_StructInit(
	ninteg_trapz_init_s *pInitStruct)
{
	pInitStruct->accumulate_flag		= NINTEG_DISABLE;
	pInitStruct->integratePeriod		= (__NINTEG_FPT__) 0.0;
	pInitStruct->accumDataSaturation	= (__NINTEG_FPT__) 0.0;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      25-мар-2019
 *
 * @brief    Функция инициализирует структуру типа "ninteg_trapz_s"
 *
 * @param[out] 	*pTrapz_s:	Указатель на структуру для выполнения
 * 							численного интегрирования методом трапеций
 * @param[in]   *pInit_s:   Указатель на структуру, содержащую начальные
 * 							параметры для записи в "pTrapz_s"
 *
 * @return Статус инициализации
 */
ninteg_fnc_status_e
NINTEG_Trapz_Init(
	ninteg_trapz_s			*pTrapz_s,
	ninteg_trapz_init_s 	*pInit_s)
{
	/* Если период интегрирования равен нулю */
	if (pInit_s->integratePeriod == ((__NINTEG_FPT__) 0.0))
	{
		pTrapz_s->initStatus_e = NINTEG_ERROR;
	}
	/* Если включено аккумулирование интегратора и не задано насыщение */
	else if ((pInit_s->accumulate_flag == NINTEG_ENABLE)
			 && (pInit_s->accumDataSaturation == ((__NINTEG_FPT__) 0.0)))
	{
		pTrapz_s->initStatus_e = NINTEG_ERROR;
	}
	else
	{
		pTrapz_s->dT 					= pInit_s->integratePeriod;
		pTrapz_s->deltaData 			= 0.0;
		pTrapz_s->previousData 			= 0.0;
		pTrapz_s->tumblers_s.accumEn 	= pInit_s->accumulate_flag;
		pTrapz_s->accumDataSaturation	= pInit_s->accumDataSaturation;

		pTrapz_s->initStatus_e = NINTEG_SUCCESS;
	}

	return (pTrapz_s->initStatus_e);
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
__NINTEG_FORCE_INLINE __NINTEG_FPT__ __NINTEG_FNC_LOOP_OPTIMIZE_MODE
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
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
