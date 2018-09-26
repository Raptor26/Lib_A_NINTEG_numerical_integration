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
	__NUNTEG_FPT__ *pPreviousAngleVelocityArr,
	__NUNTEG_FPT__ *pCurrentAngleVelocityArr,
	__NUNTEG_FPT__ deltaTimeInSec,
	__NUNTEG_FPT__ *pDeltaAnglesArr)
{
	//  Нахождение дельты угла по оси X;
	*pDeltaAnglesArr++ =
		NINTEG_IntegrateAnglVelocityTrapezium(
			pPreviousAngleVelocityArr++,
			pCurrentAngleVelocityArr++,
			deltaTimeInSec);

	//  Нахождение дельты угла по оси Y;
	*pDeltaAnglesArr++ =
		NINTEG_IntegrateAnglVelocityTrapezium(
			pPreviousAngleVelocityArr++,
			pCurrentAngleVelocityArr++,
			deltaTimeInSec);

	//  Нахождение дельты угла по оси Z;
	*pDeltaAnglesArr =
		NINTEG_IntegrateAnglVelocityTrapezium(
			pPreviousAngleVelocityArr,
			pCurrentAngleVelocityArr,
			deltaTimeInSec);
}

__NUNTEG_FPT__ NINTEG_IntegrateAnglVelocityTrapezium(
	__NUNTEG_FPT__ *pPreviousAngleVelocity,
	__NUNTEG_FPT__ *pCurrentAngleVelocity,
	__NUNTEG_FPT__ deltaTimeInSec)
{
	//  Нахождение угла на основе текущей угловой скорости и угловой скорости в
	//  предыдущий момент времени;
	__NUNTEG_FPT__ deltaAngel =
		(*pPreviousAngleVelocity + *pCurrentAngleVelocity) * deltaTimeInSec * 0.5f;

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
__NUNTEG_FPT__ NINTEG_Trapz(
	ninteg_trapz_s *pTrapz_s,
	__NUNTEG_FPT__ newData)
{
	// Численное интегрирование методом трапеций;
	pTrapz_s->deltaData =
		(pTrapz_s->previousData + newData) * pTrapz_s->dT * 0.5f;

	// Копирование текущего значения переменной в переменную данных за предыдущий момент времени;
	pTrapz_s->previousData = newData;

	/* Если разрешено аккумулирование методом трапеций */
	if (pTrapz_s->tumblers_s.accumEn == 1)
	{
		/* Инкремент аккумулятора */
		pTrapz_s->accumData += pTrapz_s->deltaData;

		/* Возврат аккумулированного значения */
		return (pTrapz_s->accumData);
	}
	else
	{
		/* Возврат дельты за промежуток времени */
		return pTrapz_s->deltaData;
	}
}

/**
 * @brief   Функция инициализирует структуру типа NINTEG_find_delta_trapezium_s;
 * @param   *pStruct:   Указатель на структуру, в которой содержатся данные для
 *                      нахождения дельты величины между вызовами функции
 *                      NINTEG_FindDeltaTrapezium();
 * @param   dT: Период времени в секундах, для нахождения приращения величины;
 * @return  None;
 */
void NINTEG_InitStruct_Trapz(
	ninteg_trapz_s *pStruct,
	__NUNTEG_FPT__ dT)
{
	pStruct->dT = dT;
	pStruct->deltaData = 0.0f;
	pStruct->previousData = 0.0f;
	pStruct->tumblers_s.accumEn = 0;
}

ninteg_fnc_status_e
NINTEG_Trapz_Init(
	ninteg_trapz_s			 	*p_s,
	ninteg_trapz_InitStruct_s 	*pInitStruct)
{
	if (pInitStruct->integratePeriod == (__NUNTEG_FPT__) 0.0)
	{
		return NINTEG_ERROR;
	}

	p_s->dT 					= pInitStruct->integratePeriod;
	p_s->deltaData 				= 0.0;
	p_s->previousData 			= 0.0;
	p_s->tumblers_s.accumEn 	= pInitStruct->accumulate_flag;

	return NINTEG_SUCCESS;
}
/*============================================================================*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
