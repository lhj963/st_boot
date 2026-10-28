/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * NXP Confidential. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

#ifndef LPTMR_HW_ACCESS_H
#define LPTMR_HW_ACCESS_H

/*!
 * @file lptmr_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, Expression assigned to a narrower or different essential type
 * The cast is used to convert from uint32_t to enum_type.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum<i>'
 * The cast is used to convert from uint32_t to enum_type.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device_registers.h"
#include "lptmr_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the LPTMR instance to reset values.
 *
 * This function initializes all registers of the LPTMR instance to a known state (the register
 * are written with their reset values from the Reference Manual).
 *
 * @param[in] base - LPTMR base pointer
 *
 */
void LPTMR_Init(LPTMR_Type* const base);



bool LPTMR_GetDmaRequest(const LPTMR_Type* const base);


void LPTMR_SetDmaRequest(LPTMR_Type* const base,
									 bool enable);


bool LPTMR_GetCompareFlag(const LPTMR_Type* const base);


void LPTMR_ClearCompareFlag(LPTMR_Type* const base);


bool LPTMR_GetInterruptEnable(const LPTMR_Type* const base);


void LPTMR_SetInterrupt(LPTMR_Type* const base,
									bool enable);


lptmr_pinselect_t LPTMR_GetPinSelect(const LPTMR_Type* const base);


void LPTMR_SetPinSelect(LPTMR_Type* const base,
									const lptmr_pinselect_t pinsel);


lptmr_pinpolarity_t LPTMR_GetPinPolarity(const LPTMR_Type* const base);


void LPTMR_SetPinPolarity(LPTMR_Type* const base,
									  const lptmr_pinpolarity_t pol);


bool LPTMR_GetFreeRunning(const LPTMR_Type* const base);


void LPTMR_SetFreeRunning(LPTMR_Type* const base,
									  const bool enable);


lptmr_workmode_t LPTMR_GetWorkMode(const LPTMR_Type* const base);


void LPTMR_SetWorkMode(LPTMR_Type* const base,
								   const lptmr_workmode_t mode);


bool LPTMR_GetEnable(const LPTMR_Type* const base);


void LPTMR_Enable(LPTMR_Type* const base);


void LPTMR_Disable(LPTMR_Type* const base);


lptmr_prescaler_t LPTMR_GetPrescaler(const LPTMR_Type* const base);


void LPTMR_SetPrescaler(LPTMR_Type* const base,
									const lptmr_prescaler_t presc);


bool LPTMR_GetBypass(const LPTMR_Type* const base);


void LPTMR_SetBypass(LPTMR_Type* const base,
								 const bool enable);


lptmr_clocksource_t LPTMR_GetClockSelect(const LPTMR_Type* const base);


void LPTMR_SetClockSelect(LPTMR_Type* const base,
									  const lptmr_clocksource_t clocksel);


uint16_t LPTMR_GetCompareValue(const LPTMR_Type* const base);


void LPTMR_SetCompareValue(LPTMR_Type* const base,
									   const uint16_t compval);


uint16_t LPTMR_GetCounterValue(LPTMR_Type* const base);



#if defined(__cplusplus)
}
#endif

#endif /* LPTMR_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
