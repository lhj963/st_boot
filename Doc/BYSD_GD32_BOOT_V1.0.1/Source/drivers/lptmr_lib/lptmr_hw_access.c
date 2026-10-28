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

/*!
 * @file lptmr_hw_access.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 */

#include "lptmr_hw_access.h"

bool LPTMR_GetDmaRequest(const LPTMR_Type* base)
{
    uint32_t tmp = base->CSR;

    tmp = (tmp & LPTMR_CSR_TDRE_MASK) >> LPTMR_CSR_TDRE_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Configure the DMA Request Enable Flag state
 *
 * This function configures the DMA Request feature of the LPTMR. If enabled,
 * a DMA Request is issued when the Compare Match event occurs. If enabled, the
 * Compare Match/Interrupt Pending flag is cleared when the DMA controller is
 * done.
 *
 * @param[in] base   - LPTMR base pointer
 * @param[in] enable - The new state of the DMA Request Enable Flag
 *      - true: enable DMA Request
 *      - false: disable DMA Request
 */
  void LPTMR_SetDmaRequest(LPTMR_Type* const base,
                                       bool enable)
{

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TDRE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TDRE(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

/*!
 * @brief Get the Compare Flag state
 *
 * This function checks whether a Compare Match event has occurred or if there is
 * an Interrupt Pending.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Compare Flag state
 *      - true: Compare Match/Interrupt Pending asserted
 *      - false: Compare Match/Interrupt Pending not asserted
 */
  bool LPTMR_GetCompareFlag(const LPTMR_Type* const base)
{
 

    uint32_t tmp = base -> CSR;
    tmp = (tmp & LPTMR_CSR_TCF_MASK) >> LPTMR_CSR_TCF_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Clear the Compare Flag
 *
 * This function clears the Compare Flag/Interrupt Pending state.
 *
 * @param[in] base - LPTMR base pointer
 */
  void LPTMR_ClearCompareFlag(LPTMR_Type* const base)
{


    uint32_t tmp = base->CSR;
    tmp |= (LPTMR_CSR_TCF_MASK);
    base->CSR = tmp;
#ifdef ERRATA_E9005
    /* Read-after-write sequence to guarantee required serialization of memory operations */
    (void)base->CSR;
#endif
}

/*!
 * @brief Get the Interrupt Enable state
 *
 * This function returns the Interrupt Enable state for the LPTMR. If enabled,
 * an interrupt is generated when a Compare Match event occurs.
 *
 * @param[in] base - LPTMR base pointer
 * @return Interrupt Enable state
 *      - true: Interrupt enabled
 *      - false: Interrupt disabled
 */
  bool LPTMR_GetInterruptEnable(const LPTMR_Type* const base)
{

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TIE_MASK) >> LPTMR_CSR_TIE_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Configure the Interrupt Enable state
 *
 * This function configures the Interrupt Enable state for the LPTMR. If enabled,
 * an interrupt is generated when a Compare Match event occurs.
 *
 * @param[in] base   - LPTMR base pointer
 * @param[in] enable - The new state for the interrupt
 *          - true: enable Interrupt
 *          - false: disable Interrupt
 */
  void LPTMR_SetInterrupt(LPTMR_Type* const base,
                                      bool enable)
{
 

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TIE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TIE(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

/*!
 * @brief Get the Pin select for Counter Mode
 *
 * This function returns the configured Input Pin for Pulse Counter Mode.
 *
 * @param[in] base - LPTMR base pointer
 * @return Input pin selection
 *          - LPTMR_PINSELECT_TRGMUX: count pulses from TRGMUX output
 *          - LPTMR_PINSELECT_ALT1: count pulses from pin alt 1
 *          - LPTMR_PINSELECT_ALT2: count pulses from pin alt 2
 *          - LPTMR_PINSELECT_ALT3: count pulses from pin alt 3
 */
  lptmr_pinselect_t LPTMR_GetPinSelect(const LPTMR_Type* const base)
{
  

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TPS_MASK) >> LPTMR_CSR_TPS_SHIFT;
    return (lptmr_pinselect_t)(tmp);
}

/*!
 * @brief Configure the Pin selection for Pulse Counter Mode
 *
 * This function configures the input Pin selection for Pulse Counter Mode.
 * This feature can be configured only when the LPTMR is disabled.
 *
 * @param[in] base   - LPTMR base pointer
 * @param[in] pinsel - Pin selection
 *          - LPTMR_PINSELECT_TRGMUX: count pulses from TRGMUX output
 *          - LPTMR_PINSELECT_ALT1: count pulses from pin alt 1
 *          - LPTMR_PINSELECT_ALT2: count pulses from pin alt 2
 *          - LPTMR_PINSELECT_ALT3: count pulses from pin alt 3
 */
  void LPTMR_SetPinSelect(LPTMR_Type* const base,
                                      const lptmr_pinselect_t pinsel)
{
 

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TPS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TPS(pinsel);
    base->CSR = tmp;
}

/*!
 * @brief Get Pin Polarity for Pulse Counter Mode
 *
 * This function returns the configured pin polarity that triggers an increment
 * in Pulse Counter Mode.
 *
 * @param[in] base - LPTMR base pointer
 * @return The pin polarity for Pulse Counter Mode
 *          - LPTMR_PINPOLARITY_RISING: count pulse on Rising Edge
 *          - LPTMR_PINPOLARITY_FALLING: count pulse on Falling Edge
 */
  lptmr_pinpolarity_t LPTMR_GetPinPolarity(const LPTMR_Type* const base)
{

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TPP_MASK) >> LPTMR_CSR_TPP_SHIFT;

    return (lptmr_pinpolarity_t)((tmp == 0u) ? LPTMR_PINPOLARITY_RISING : LPTMR_PINPOLARITY_FALLING);
}

/*!
 * @brief Configure Pin Polarity for Pulse Counter Mode
 *
 * This function configures the pin polarity that triggers an increment in Pulse
 * Counter Mode. This feature can be configured only when the LPTMR is disabled.
 *
 * @param[in] base - LPTMR base pointer
 * @param[in] pol  - The pin polarity to count in Pulse Counter Mode
 *          - LPTMR_PINPOLARITY_RISING: count pulse on Rising Edge
 *          - LPTMR_PINPOLARITY_FALLING: count pulse on Falling Edge
 */
  void LPTMR_SetPinPolarity(LPTMR_Type* const base,
                                        const lptmr_pinpolarity_t pol)
{
    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TPP_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TPP(pol);
    base->CSR = tmp;
}

/*!
 * @brief Get the Free Running state
 *
 * This function checks whether the Free Running feature of the LPTMR is enabled
 * or disabled.
 *
 * @param[in] base - LPTMR base pointer
 * @return Free running mode state
 *          - true: Free Running Mode enabled. Reset counter on 16-bit overflow
 *          - false: Free Running Mode disabled. Reset counter on Compare Match.
 */
  bool LPTMR_GetFreeRunning(const LPTMR_Type* const base)
{


    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TFC_MASK) >> LPTMR_CSR_TFC_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Configure the Free Running state
 *
 * This function configures the Free Running feature of the LPTMR. This feature
 * can be configured only when the LPTMR is disabled.
 *
 * @param[in] base   - LPTMR base pointer
 * @param[in] enable - The new Free Running state
 *          - true: Free Running Mode enabled. Reset counter on 16-bit overflow
 *          - false: Free Running Mode disabled. Reset counter on Compare Match.
 */
  void LPTMR_SetFreeRunning(LPTMR_Type* const base,
                                        const bool enable)
{

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TFC_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TFC(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

/*!
 * @brief Get current Work Mode
 *
 * This function returns the currently configured Work Mode for the LPTMR.
 *
 *
 * @param[in] base - LPTMR base pointer
 * @return Work Mode
 *          - LPTMR_WORKMODE_TIMER: LPTMR is in Timer Mode
 *          - LPTMR_WORKMODE_PULSECOUNTER: LPTMR is in Pulse Counter Mode
 */
  lptmr_workmode_t LPTMR_GetWorkMode(const LPTMR_Type* const base)
{

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TMS_MASK) >> LPTMR_CSR_TMS_SHIFT;

    return (lptmr_workmode_t)((tmp == 0u) ? LPTMR_WORKMODE_TIMER : LPTMR_WORKMODE_PULSECOUNTER);
}

/*!
 * @brief Configure the Work Mode
 *
 * This function configures the LPTMR to either Timer Mode or Pulse Counter
 * Mode. This feature can be configured only when the LPTMR is disabled.
 *
 * @param[in] base - LPTMR base pointer
 * @param[in] mode - New Work Mode
 *          - LPTMR_WORKMODE_TIMER: LPTMR set to Timer Mode
 *          - LPTMR_WORKMODE_PULSECOUNTER: LPTMR set to Pulse Counter Mode
 */
  void LPTMR_SetWorkMode(LPTMR_Type* const base,
                                     const lptmr_workmode_t mode)
{

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TMS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TMS(mode);
    base->CSR = tmp;
}

/*!
 * @brief Get the Enable state.
 *
 * Prior to reconfiguring the LPTMR, it is necessary to disable it.
 *
 * @param[in] base - LPTMR base pointer
 * @return The state of the LPTMR
 *          - true: LPTMR enabled
 *          - false: LPTMR disabled
 */
  bool LPTMR_GetEnable(const LPTMR_Type* const base)
{

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TEN_MASK) >> LPTMR_CSR_TEN_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Enable the LPTMR
 *
 * Enable the LPTMR. Starts the timer/counter.
 *
 *
 * @param[in] base - LPTMR base pointer
 */
  void LPTMR_Enable(LPTMR_Type* const base)
{
    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TEN(1u);
    base->CSR = tmp;
}

/*!
 * @brief Disable the LPTMR
 *
 * Disable the LPTMR. Stop the Counter/Timer and allow reconfiguration.
 *
 * @param[in] base - LPTMR base pointer
 */
  void LPTMR_Disable(LPTMR_Type* const base)
{

    uint32_t tmp = base->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TEN(0u);
    base->CSR = tmp;
}

/*!
 * @brief Get Prescaler/Glitch Filter divider value
 *
 * This function returns the currently configured Prescaler/Glitch Filter divider
 * value.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Prescaler/Glitch filter value
 *          - LPTMR_PRESCALE_2: Timer mode: prescaler 2, Glitch filter mode: invalid
 *          - LPTMR_PRESCALE_4_GLITCHFILTER_2: Timer mode: prescaler 4, Glitch filter mode: 2 clocks
 *          - LPTMR_PRESCALE_8_GLITCHFILTER_4: Timer mode: prescaler 8, Glitch filter mode: 4 clocks
 *          - LPTMR_PRESCALE_16_GLITCHFILTER_8: Timer mode: prescaler 16, Glitch filter mode: 8 clocks
 *          - LPTMR_PRESCALE_32_GLITCHFILTER_16: Timer mode: prescaler 32, Glitch filter mode: 16 clocks
 *          - LPTMR_PRESCALE_64_GLITCHFILTER_32: Timer mode: prescaler 64, Glitch filter mode: 32 clocks
 *          - LPTMR_PRESCALE_128_GLITCHFILTER_64: Timer mode: prescaler 128, Glitch filter mode: 64 clocks
 *          - LPTMR_PRESCALE_256_GLITCHFILTER_128: Timer mode: prescaler 256, Glitch filter mode: 128 clocks
 *          - LPTMR_PRESCALE_512_GLITCHFILTER_256: Timer mode: prescaler 512, Glitch filter mode: 256 clocks
 *          - LPTMR_PRESCALE_1024_GLITCHFILTER_512: Timer mode: prescaler 1024, Glitch filter mode: 512 clocks
 *          - LPTMR_PRESCALE_2048_GLITCHFILTER_1024: Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks
 *          - LPTMR_PRESCALE_4096_GLITCHFILTER_2048: Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks
 *          - LPTMR_PRESCALE_8192_GLITCHFILTER_4096: Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks
 *          - LPTMR_PRESCALE_16384_GLITCHFILTER_8192: Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks
 *          - LPTMR_PRESCALE_32768_GLITCHFILTER_16384: Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks
 *          - LPTMR_PRESCALE_65536_GLITCHFILTER_32768: Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks
 */
  lptmr_prescaler_t LPTMR_GetPrescaler(const LPTMR_Type* const base)
{

    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PRESCALE_MASK) >> LPTMR_PSR_PRESCALE_SHIFT;
    return (lptmr_prescaler_t)(tmp);
}

/*!
 * @brief Configure the Prescaler/Glitch Filter divider value
 *
 * This function configures the value for the Prescaler/Glitch Filter. This
 * feature can be configured only when the LPTMR is disabled.
 *
 * @param[in] base  - LPTMR base pointer
 * @param[in] presc - The new Prescaler value
 *          - LPTMR_PRESCALE_2: Timer mode: prescaler 2, Glitch filter mode: invalid
 *          - LPTMR_PRESCALE_4_GLITCHFILTER_2: Timer mode: prescaler 4, Glitch filter mode: 2 clocks
 *          - LPTMR_PRESCALE_8_GLITCHFILTER_4: Timer mode: prescaler 8, Glitch filter mode: 4 clocks
 *          - LPTMR_PRESCALE_16_GLITCHFILTER_8: Timer mode: prescaler 16, Glitch filter mode: 8 clocks
 *          - LPTMR_PRESCALE_32_GLITCHFILTER_16: Timer mode: prescaler 32, Glitch filter mode: 16 clocks
 *          - LPTMR_PRESCALE_64_GLITCHFILTER_32: Timer mode: prescaler 64, Glitch filter mode: 32 clocks
 *          - LPTMR_PRESCALE_128_GLITCHFILTER_64: Timer mode: prescaler 128, Glitch filter mode: 64 clocks
 *          - LPTMR_PRESCALE_256_GLITCHFILTER_128: Timer mode: prescaler 256, Glitch filter mode: 128 clocks
 *          - LPTMR_PRESCALE_512_GLITCHFILTER_256: Timer mode: prescaler 512, Glitch filter mode: 256 clocks
 *          - LPTMR_PRESCALE_1024_GLITCHFILTER_512: Timer mode: prescaler 1024, Glitch filter mode: 512 clocks
 *          - LPTMR_PRESCALE_2048_GLITCHFILTER_1024: Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks
 *          - LPTMR_PRESCALE_4096_GLITCHFILTER_2048: Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks
 *          - LPTMR_PRESCALE_8192_GLITCHFILTER_4096: Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks
 *          - LPTMR_PRESCALE_16384_GLITCHFILTER_8192: Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks
 *          - LPTMR_PRESCALE_32768_GLITCHFILTER_16384: Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks
 *          - LPTMR_PRESCALE_65536_GLITCHFILTER_32768: Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks
 */
  void LPTMR_SetPrescaler(LPTMR_Type* const base,
                                      const lptmr_prescaler_t presc)
{

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PRESCALE_MASK);
    tmp |= LPTMR_PSR_PRESCALE(presc);
    base->PSR = tmp;
}

/*!
 * @brief Get the Prescaler/Glitch Filter Bypass enable state
 *
 * This function checks whether the Prescaler/Glitch Filter Bypass is enabled.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Prescaler Bypass state
 *          - true: Prescaler/Glitch Filter Bypass enabled
 *          - false: Prescaler/Glitch Filter Bypass disabled
 */
  bool LPTMR_GetBypass(const LPTMR_Type* const base)
{
    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PBYP_MASK) >> LPTMR_PSR_PBYP_SHIFT;

    return ((tmp == 1u) ? true : false);
}

/*!
 * @brief Configure the Prescaler/Glitch Filter Bypass enable state
 *
 * This function configures the Prescaler/Glitch filter Bypass. This feature
 * can be configured only when the LPTMR is disabled.
 *
 * @param[in] base  - LPTMR base pointer
 * @param[in] enable - The new Prescaler/Glitch Filter Bypass state
 *          - true: Prescaler/Glitch Filter Bypass enabled
 *          - false: Prescaler/Glitch Filter Bypass disabled
 */
  void LPTMR_SetBypass(LPTMR_Type* const base,
                                   const bool enable)
{

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PBYP_MASK);
    tmp |= LPTMR_PSR_PBYP(enable ? (uint32_t)1u : (uint32_t)0u);
    base->PSR = tmp;
}

/*!
 * @brief Get the LPTMR input Clock selection
 *
 * This function returns the current configured input Clock for the LPTMR.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Clock source
 *          - LPTMR_CLOCKSOURCE_SIRCDIV2: clock from SIRC DIV2
 *          - LPTMR_CLOCKSOURCE_1KHZ_LPO: clock from 1kHz LPO
 *          - LPTMR_CLOCKSOURCE_RTC: clock from RTC
 *          - LPTMR_CLOCKSOURCE_PCC: clock from PCC
 */
  lptmr_clocksource_t LPTMR_GetClockSelect(const LPTMR_Type* const base)
{

    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PCS_MASK) >> LPTMR_PSR_PCS_SHIFT;
    return (lptmr_clocksource_t)(tmp);
}

/*!
 * @brief Configure the LPTMR input Clock selection
 *
 * This function configures a clock source for the LPTMR. This feature can be
 * configured only when the LPTMR is disabled.
 *
 * @param[in] base - LPTMR base pointer
 * @param[in] clocksel - New Clock Source
 *          - LPTMR_CLOCKSOURCE_SIRCDIV2: clock from SIRC DIV2
 *          - LPTMR_CLOCKSOURCE_1KHZ_LPO: clock from 1kHz LPO
 *          - LPTMR_CLOCKSOURCE_RTC: clock from RTC
 *          - LPTMR_CLOCKSOURCE_PCC: clock from PCC
 */
  void LPTMR_SetClockSelect(LPTMR_Type* const base,
                                        const lptmr_clocksource_t clocksel)
{

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PCS_MASK);
    tmp |= LPTMR_PSR_PCS(3);
    base->PSR = tmp;
}

/*!
 * @brief Get the Compare Value
 *
 * This function returns the current Compare Value.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Compare Value
 */
  uint16_t LPTMR_GetCompareValue(const LPTMR_Type* const base)
{

    uint32_t tmp = base->CMR;
    tmp = (tmp & LPTMR_CMR_COMPARE_MASK) >> LPTMR_CMR_COMPARE_SHIFT;
    return (uint16_t)(tmp);
}

/*!
 * @brief Configure the Compare Value
 *
 * This function configures the Compare Value. If set to 0, the Compare Match
 * event and the hardware trigger assert and remain asserted until the timer is
 * disabled.
 *
 * @param[in] base - LPTMR base pointer
 * @param[in] compval - The new Compare Value
 */
  void LPTMR_SetCompareValue(LPTMR_Type* const base,
                                         const uint16_t compval)
{

    uint32_t tmp = base->CMR;
    tmp &= ~(LPTMR_CMR_COMPARE_MASK);
    tmp |= LPTMR_CMR_COMPARE(compval);
    base->CMR = tmp;
}

/*!
 * @brief Get the current Counter Value
 *
 * This function returns the Counter Value.
 *
 * @param[in] base - LPTMR base pointer
 * @return The Counter Value
 */
  uint16_t LPTMR_GetCounterValue(LPTMR_Type* const base)
{
			uint16_t cnr;
	/* Write dummy value before reading register */
    base->CNR = LPTMR_CNR_COUNTER(0u);
    cnr = (uint16_t)base->CNR;
    return cnr;
}


void LPTMR_Init(LPTMR_Type* const base)
{
    uint32_t tmp = base->CSR;
 
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TEN(0u);
    base->CSR = tmp;

    base->CSR = LPTMR_CSR_TEN(0u) | \
                LPTMR_CSR_TMS(0u) | \
                LPTMR_CSR_TFC(0u) | \
                LPTMR_CSR_TPP(0u) | \
                LPTMR_CSR_TPS(0u) | \
                LPTMR_CSR_TIE(0u) | \
                LPTMR_CSR_TCF(0u) | \
                LPTMR_CSR_TDRE(0u);

    base->PSR = LPTMR_PSR_PCS(0u) | \
                LPTMR_PSR_PBYP(0u) | \
                LPTMR_PSR_PRESCALE(0u);

    base->CMR = LPTMR_CMR_COMPARE(0u);
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
