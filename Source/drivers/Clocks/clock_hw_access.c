#include "clock_hw_access.h"


/*!
* @brief Sets SOSC control register
*
* @param[in] base        pcc base pointer
* @param[in] monitorMode clock monitor enablement
* @param[in] clockGate    control register can be written or not
*/
 void PCC_SetPeripheralClockControl(PCC_Type* base, clock_names_t clockName, bool clockGate, uint32_t clockSource, uint32_t divider, uint32_t multiplier)
{
   /* Configure the peripheral clock source, the fractional clock divider and the clock gate */
   uint32_t value =  PCC_PCCn_PCS(clockSource)              |
                     PCC_PCCn_FRAC(multiplier)              |
                     PCC_PCCn_PCD(divider)                  |
                     PCC_PCCn_CGC(clockGate ? 1UL : 0UL );

   base->PCCn[clockNameMappings[clockName]] = value;
}

/*!
* @brief Enables/disables the clock for a given peripheral.
* For example, to enable the ADC0 clock, use like this:
* @code
*  PCC_SetClockMode(PCC, PCC_ADC0_CLOCK, true);
* @endcode
*
* @param[in] base        pcc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from S32K144_clock_names.h)
*    PCC_DMA0_CLOCK
*    PCC_MPU0_CLOCK
*    ...
*    PCC_LPUART3_CLOCK
* @param[in] isClockEnabled  is the value of the command that enables/disables the clock
*/
 void PCC_SetClockMode(PCC_Type* const base,
                                       const clock_names_t clockName,
                                       const bool isClockEnabled)
{
   if (isClockEnabled)
   {
       base->PCCn[clockNameMappings[clockName]] |= PCC_PCCn_CGC(1UL);
   }
   else
   {
       base->PCCn[clockNameMappings[clockName]] &= (uint32_t)(~(PCC_PCCn_CGC_MASK));
   }
}



/*!
* @brief Gets the clock gate control mode.
*
* @param[in] base        pcc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from S32K144_clock_names.h)
*    PCC_DMA0_CLOCK
*    PCC_MPU0_CLOCK
*    ...
*    PCC_LPUART3_CLOCK
* @return  the clock gate control mode
*        - false : Clock is disabled
*        - true : Clock is enabled
*/
 bool PCC_GetClockMode(const PCC_Type* const base,
                                       const clock_names_t clockName)
{
   uint32_t regValue = (uint32_t)base->PCCn[clockNameMappings[clockName]];
   regValue = (regValue & PCC_PCCn_CGC_MASK) >> PCC_PCCn_CGC_SHIFT;
   return (regValue == 0U) ? false : true;
}

/*!
* @brief Gets the selection of a clock source for a specific peripheral
*
* @param[in] base        pcc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from S32K144_clock_names.h)
*    PCC_DMA0_CLOCK
*    PCC_MPU0_CLOCK
*    ...
*    PCC_LPUART3_CLOCK
* @return  the clock source
*/
 uint32_t PCC_GetClockSourceSel(const PCC_Type* const base,
                                                                 const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_PCS_MASK) >> PCC_PCCn_PCS_SHIFT);
}

/*!
* @brief Gets the selection of the fractional value for a specific peripheral
*
* @param[in] base        pcc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from S32K144_clock_names.h)
*    PCC_DMA0_CLOCK
*    PCC_MPU0_CLOCK
*    ...
*    PCC_LPUART3_CLOCK
* @return  the fractional value
*        - PCC_MULTPCCnLY_BY_ONE : Fractional value is zero
*        - PCC_MULTPCCnLY_BY_TWO : Fractional value is one
*/
 uint32_t PCC_GetFracValueSel(const PCC_Type* const base,
                                               const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_FRAC_MASK) >> PCC_PCCn_FRAC_SHIFT);
}

/*!
* @brief Gets the selection of the divider value for a specific peripheral
*
* @param[in] base        pcc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from S32K144_clock_names.h)
*    PCC_DMA0_CLOCK
*    PCC_MPU0_CLOCK
*    ...
*    PCC_LPUART3_CLOCK
* @return  the divider value
*        - PCC_DIVIDE_BY_ONE   : Divide by 1
*        - PCC_DIVIDE_BY_TWO   : Divide by 2
*        - PCC_DIVIDE_BY_THREE : Divide by 3
*        - PCC_DIVIDE_BY_FOUR  : Divide by 4
*        - PCC_DIVIDE_BY_FIVE  : Divide by 5
*        - PCC_DIVIDE_BY_SIX   : Divide by 6
*        - PCC_DIVIDE_BY_SEVEN : Divide by 7
*        - PCC_DIVIDE_BY_EIGTH : Divide by 8
*/
 uint32_t PCC_GetDividerSel(const PCC_Type* const base,
                                             const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_PCD_MASK) >> PCC_PCCn_PCD_SHIFT);
}

uint32_t SMC_GetCurrentRunningMode(const SMC_Type* const baseAddr)
{
    return (baseAddr->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) >> SMC_PMSTAT_PMSTAT_SHIFT;
}


/*!
 * @brief Get SCG ClockOut source select
 *
 * This function gets the SCG clockOut source
 *
 * @param[in] base Register base address for the SCG instance.
 * @return ClockOut source.
 */
  uint32_t SCG_GetClockoutSourceSel(const SCG_Type * base)
{
    return (base->CLKOUTCNFG & SCG_CLKOUTCNFG_CLKOUTSEL_MASK) >> SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT;
}


/*!
 * @brief Gets SCG current system clock source
 *
 * This function gets the current system clock source.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current system clock source.
 */
  uint32_t SCG_GetCurrentSystemClockSource(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT);
}

/*!
 * @brief Gets SCG Current Core Clock Divide Ratio
 *
 * This function gets the Current Core Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Core Clock Divide Ratio.
 */
  uint32_t SCG_GetCurrentCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT);
}

/*!
 * @brief Gets SCG Current Bus Clock Divide Ratio
 *
 * This function gets the Current Bus Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Bus Clock Divide Ratio.
 */
  uint32_t SCG_GetCurrentBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVBUS_MASK) >> SCG_CSR_DIVBUS_SHIFT);
}

/*!
 * @brief Gets SCG Current Slow Clock Divide Ratio
 *
 * This function gets the Current Slow Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Slow Clock Divide Ratio.
 */
  uint32_t SCG_GetCurrentSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVSLOW_MASK) >> SCG_CSR_DIVSLOW_SHIFT);
}

/*!
 * @brief Sets SCG run system clock
 *
 * This function sets the RUN clock control (system clock source, bus, core and slow dividers).
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base System clock configuration address.
 */
  void SCG_SetRunClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
    uint32_t value = (uint32_t)(((source      << SCG_RCCR_SCS_SHIFT)     & SCG_RCCR_SCS_MASK)     |
                                ((coreDivider << SCG_RCCR_DIVCORE_SHIFT) & SCG_RCCR_DIVCORE_MASK) |
                                ((busDivider  << SCG_RCCR_DIVBUS_SHIFT)  & SCG_RCCR_DIVBUS_MASK)  |
                                ((slowDivider << SCG_RCCR_DIVSLOW_SHIFT) & SCG_RCCR_DIVSLOW_MASK) );
    base->RCCR = value;
}

/*!
 * @brief Sets SCG vlpr system clock
 *
 * This function sets the VLPR clock control (system clock source, bus, core and slow dividers).
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base System clock configuration address.
 */
  void SCG_SetVlprClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
    uint32_t value = (uint32_t)(((source      << SCG_VCCR_SCS_SHIFT)     & SCG_VCCR_SCS_MASK)     |
                                ((coreDivider << SCG_VCCR_DIVCORE_SHIFT) & SCG_VCCR_DIVCORE_MASK) |
                                ((busDivider  << SCG_VCCR_DIVBUS_SHIFT)  & SCG_VCCR_DIVBUS_MASK)  |
                                ((slowDivider << SCG_VCCR_DIVSLOW_SHIFT) & SCG_VCCR_DIVSLOW_MASK) );

    base->VCCR = value;
}

/*!
 * @brief Gets the first asynchronous divider for FIRC.
 *
 * This function gets the first asynchronous divider for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return FIRC first asynchronous divider
 */
  uint32_t SCG_GetFircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV1_MASK) >> SCG_FIRCDIV_FIRCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for FIRC.
 *
 * This function gets the second asynchronous divider for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return FIRC second asynchronous divider
 */
  uint32_t SCG_GetFircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV2_MASK) >> SCG_FIRCDIV_FIRCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for FIRC.
 *
 * This function sets SCG asynchronous dividers for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
  void SCG_SetFircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_FIRCDIV_FIRCDIV1_SHIFT) & SCG_FIRCDIV_FIRCDIV1_MASK)     |
                                ((div2 << SCG_FIRCDIV_FIRCDIV2_SHIFT) & SCG_FIRCDIV_FIRCDIV2_MASK) );
    base->FIRCDIV = value;
}


/*!
 * @brief Gets the first asynchronous divider for SIRC.
 *
 * This function gets the first asynchronous divider for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SIRC first asynchronous divider
 */
  uint32_t SCG_GetSircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV1_MASK) >> SCG_SIRCDIV_SIRCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SIRC.
 *
 * This function gets the second asynchronous divider for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SIRC second asynchronous divider
 */
  uint32_t SCG_GetSircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV2_MASK) >> SCG_SIRCDIV_SIRCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SIRC.
 *
 * This function sets SCG asynchronous dividers for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
  void SCG_SetSircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SIRCDIV_SIRCDIV1_SHIFT) & SCG_SIRCDIV_SIRCDIV1_MASK)     |
                                ((div2 << SCG_SIRCDIV_SIRCDIV2_SHIFT) & SCG_SIRCDIV_SIRCDIV2_MASK) );
    base->SIRCDIV = value;
}



/*!
 * @brief Gets the first asynchronous divider for SOSC.
 *
 * This function gets the first asynchronous divider for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SOSC first asynchronous divider
 */
  uint32_t SCG_GetSoscFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV1_MASK) >> SCG_SOSCDIV_SOSCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SOSC.
 *
 * This function gets the second asynchronous divider for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SOSC second asynchronous divider
 */
  uint32_t SCG_GetSoscSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV2_MASK) >> SCG_SOSCDIV_SOSCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SOSC.
 *
 * This function sets SCG asynchronous dividers for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
  void SCG_SetSoscAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SOSCDIV_SOSCDIV1_SHIFT) & SCG_SOSCDIV_SOSCDIV1_MASK)     |
                                ((div2 << SCG_SOSCDIV_SOSCDIV2_SHIFT) & SCG_SOSCDIV_SOSCDIV2_MASK) );
    base->SOSCDIV = value;
}

#if FEATURE_HAS_SPLL_CLK
#ifdef SCG_SPLLCFG_SOURCE_MASK
/*!
 * @brief Gets the source clock for SPLL.
 *
 * This function gets the source clock for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SPLL source
 */
  uint32_t SCG_GetSourcSpll(const SCG_Type * base)
{
    return (base->SPLLCFG & SCG_SPLLCFG_SOURCE_MASK) >> SCG_SPLLCFG_SOURCE_SHIFT;
}
/*!
 * @brief Sets SCG source clock for SPLL.
 *
 * This function sets source clock for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] source for spll
 */
  void SCG_SetSourceSpll(SCG_Type * base, uint32_t source)
{
    uint32_t value = base->SPLLCFG;

    value &= ~SCG_SPLLCFG_SOURCE_MASK;
    value |= SCG_SPLLCFG_SOURCE(source);
    base->SPLLCFG = value;
}
#endif
/*!
 * @brief Gets the first asynchronous divider for SPLL.
 *
 * This function gets the first asynchronous divider for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SPLL first asynchronous divider
 */
  uint32_t SCG_GetSpllFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV1_MASK) >> SCG_SPLLDIV_SPLLDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SPLL.
 *
 * This function gets the second asynchronous divider for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SPLL second asynchronous divider
 */
  uint32_t SCG_GetSpllSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV2_MASK) >> SCG_SPLLDIV_SPLLDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SPLL.
 *
 * This function sets SCG asynchronous dividers for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
  void SCG_SetSpllAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SPLLDIV_SPLLDIV1_SHIFT) & SCG_SPLLDIV_SPLLDIV1_MASK)     |
                                ((div2 << SCG_SPLLDIV_SPLLDIV2_SHIFT) & SCG_SPLLDIV_SPLLDIV2_MASK) );
    base->SPLLDIV = value;
}
#endif

/*!
 * @brief Set SCG ClockOut source select
 *
 * This function sets the SCG ClockOut source
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] source used for ClockOut
 */
  void SCG_SetClockoutSourceSel(SCG_Type * base, uint32_t source)
{
    uint32_t regValue;

    regValue = base->CLKOUTCNFG;
    regValue &= ~(SCG_CLKOUTCNFG_CLKOUTSEL_MASK);
    regValue |= SCG_CLKOUTCNFG_CLKOUTSEL(source);
    base->CLKOUTCNFG = regValue;
}

/*!
 * @brief Gets sirc system clock mode status
 *
 * This function checks whether SIRC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc system clock mode status
 *        - false : SIRC is not the system clock source
 *        - true : SIRC is the system clock source
 */
  bool SCG_GetSircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SIRCCSR;
    regValue = (regValue & SCG_SIRCCSR_SIRCSEL_MASK) >> SCG_SIRCCSR_SIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets sirc clock status
 * This function checks whether SIRC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc  clock status
 *        - false : SIRC is not enabled or clock is not valid
 *        - true  : SIRC is enabled and clock is valid
 */
  bool SCG_GetSircStatus(const SCG_Type* const base)
{
    return (((base->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) >> SCG_SIRCCSR_SIRCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets sirc clock range
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc  range value
 */
  uint32_t SCG_GetSircRange(const SCG_Type* const base)
{
    return ((base->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT);
}

/*!
 * @brief Clears SIRC lock register
 *
 * @param[in] base        scg base pointer
 */
  void SCG_ClearSircLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SIRCCSR &= (uint32_t)(~(SCG_SIRCCSR_LK_MASK));
}


/*!
 * @brief Clears SIRC control register
 *
 * @param[in] base        scg base pointer
 */
  void SCG_ClearSircControl(SCG_Type* base)
{
    /* Clear configuration. */
    base->SIRCCSR = 0U;
}


/*!
 * @brief Sets SIRC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       sirc range value
 */
  void SCG_SetSircConfiguration(SCG_Type* base, uint8_t range)
{
    /* Set PLL configuration: frequency range */
    base->SIRCCFG = SCG_SIRCCFG_RANGE(range);
}

/*!
 * @brief Sets SIRC control register
 *
 * @param[in] base                scg base pointer
 * @param[in] enableInStop        enable in stop modes
 * @param[in] enableInLowPower    enable in very low power modes
 * @param[in] lockMode            control register can be written or not
 */
  void SCG_SetSircControl(SCG_Type* base, bool enableInStop, bool enableInLowPower, bool lockMode)
{
    uint32_t value = SCG_SIRCCSR_SIRCEN(1U)                                  |
                     SCG_SIRCCSR_SIRCSTEN(((enableInStop)     ? 1UL : 0UL )) |
                     SCG_SIRCCSR_SIRCLPEN(((enableInLowPower) ? 1UL : 0UL )) |
                     SCG_SIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SIRCCSR = value;
}


/*!
 * @brief Gets firc system clock mode status
 *
 * This function checks whether FIRC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc system clock mode status
 *        - false : FIRC is not the system clock source
 *        - true : FIRC is the system clock source
 */
  bool SCG_GetFircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->FIRCCSR;
    regValue = (regValue & SCG_FIRCCSR_FIRCSEL_MASK) >> SCG_FIRCCSR_FIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets firc clock status
 * This function checks whether FIRC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc  clock status
 *        - false : FIRC is not enabled or clock is not valid
 *        - true  : FIRC is enabled and clock is valid
 */
  bool SCG_GetFircStatus(const SCG_Type* const base)
{
    return (((base->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) >> SCG_FIRCCSR_FIRCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets firc clock range
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc  frequency range value
 */
  uint32_t SCG_GetFircRange(const SCG_Type* const base)
{
    return ((base->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT);
}

/*!
 * @brief Clears FIRC lock register
 *
 * This function clears FIRC lock.
 *
 * @param[in] base        scg base pointer
 *
 */
  void SCG_ClearFircLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->FIRCCSR &= (uint32_t)(~(SCG_FIRCCSR_LK_MASK));
}


/*!
 * @brief Clears FIRC control register
 *
 * @param[in] base        scg base pointer
 *
 */
  void SCG_ClearFircControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;
}


/*!
 * @brief Sets FIRC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       firc range value
 */
  void SCG_SetFircConfiguration(SCG_Type* base, uint8_t range)
{
    /* Set PLL configuration: frequency range */
    base->FIRCCFG = SCG_FIRCCFG_RANGE(range);
}

/*!
 * @brief Sets FIRC control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] lockMode    control register can be written or not
 */
  void SCG_SetFircControl(SCG_Type* base, bool regulator, bool lockMode)
{
    uint32_t value = SCG_FIRCCSR_FIRCEN(1U)                             |
                     SCG_FIRCCSR_FIRCREGOFF((regulator) ? 0UL : 1UL)    |
                     SCG_FIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->FIRCCSR = value;
}


/*!
 * @brief Gets sosc system clock mode status
 *
 * This function checks whether SOSC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sosc system clock mode status
 *        - false : SOSC is not the system clock source
 *        - true : SOSC is the system clock source
 */
  bool SCG_GetSoscSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SOSCCSR;
    regValue = (regValue & SCG_SOSCCSR_SOSCSEL_MASK) >> SCG_SOSCCSR_SOSCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets sosc clock status
 * This function checks whether SOSC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sosc  clock status
 *        - false : SOSC is not enabled or clock is not valid
 *        - true  : SOSC is enabled and clock is valid
 */
  bool SCG_GetSoscStatus(const SCG_Type* const base)
{
    return (((base->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) >> SCG_SOSCCSR_SOSCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Clears SOSC lock register
 *
 * @param[in] base        scg base pointer
 */
  void SCG_ClearSoscLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SOSCCSR &= (uint32_t)(~(SCG_SOSCCSR_LK_MASK));
}


/*!
 * @brief Clears SOSC control register
 *
 * @param[in] base        scg base pointer
 */
  void SCG_ClearSoscControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;
}

/*!
 * @brief Sets SOSC configuration register
 *
 * @param[in] base        scg base pointer
 */


/*!
 * @brief Sets SOSC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       sosc range
 * @param[in] gain        sosc gain
 * @param[in] extRef      external reference
 */
  void SCG_SetSoscConfiguration(SCG_Type* base, uint32_t range, uint32_t gain, uint32_t extRef)
{
    /* Set SOSC configuration. */
    base->SOSCCFG = SCG_SOSCCFG_RANGE(range)        |
                    SCG_SOSCCFG_HGO(gain)           |
                    SCG_SOSCCFG_EREFS(extRef);
}

/*!
 * @brief Sets SOSC control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] resetMode   clock monitor reset enablement
 * @param[in] lockMode    control register can be written or not
 */
  void SCG_SetSoscControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SOSCCSR_SOSCEN(1U)                        |
                     SCG_SOSCCSR_SOSCCM((monitorMode) ? 1UL : 0UL) |
                     SCG_SOSCCSR_SOSCCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SOSCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SOSCCSR = value;
}

/*!
 * @brief Enables/Disables the Low Power Oscillator.
 *
 * This function  enables/disables the Low Power Oscillator.
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @param[in] enable    enable/disable the Low Power Oscillator.
 */
  void PMC_SetLpoMode(PMC_Type* const baseAddr, const bool enable)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue &= (uint8_t)(~(PMC_REGSC_LPODIS_MASK));
    regValue |= (uint8_t)PMC_REGSC_LPODIS(enable?0U:1U);
    baseAddr->REGSC = regValue;
}

/*!
 * @brief Gets the Low Power Oscillator status.
 *
 * This function gets the Low Power Oscillator status.
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @return value LPO status
 *               false - LPO is disabled
 *               true - LPO is enabled
 */
  bool PMC_GetLpoMode(const PMC_Type * const baseAddr)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue = (uint8_t)((regValue & PMC_REGSC_LPODIS_MASK) >> PMC_REGSC_LPODIS_SHIFT);
    return (regValue == 0U) ? true : false;
}


/*!
 * @brief Low Power Oscillator Trimming Value
 *
 * This function sets the trimming value for the low power oscillator
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @param[in] value     Trimming value
 */
  void PMC_SetLpoTrimValue(PMC_Type* const baseAddr, const int8_t decimalValue)
{
    int8_t decValue = decimalValue;
    uint8_t lpotrim, trimval, regValue;

    if (decValue < 0)
    {
        lpotrim = ((uint8_t)1U) << (PMC_LPOTRIM_LPOTRIM_WIDTH);
        decValue = (int8_t)(decValue + (int8_t)(lpotrim));
    }
    trimval = (uint8_t)decValue;

    DEV_ASSERT(trimval <= (1U << PMC_LPOTRIM_LPOTRIM_WIDTH));

    regValue = baseAddr->LPOTRIM;
    regValue &= (uint8_t)(~(PMC_LPOTRIM_LPOTRIM_MASK));
    regValue |= (uint8_t)PMC_LPOTRIM_LPOTRIM(trimval);
    baseAddr->LPOTRIM = regValue;
}


/*!
 * @brief Get the clock selection of RTCCLKSEL.
 *
 * This function gets the clock selection of RTCCLKSEL.
 *
 * @param[in] base Base address for current SIM instance.
 * @return Current selection.
 */
  uint32_t SIM_GetRtcClkSrc(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_RTCCLKSEL_MASK) >> SIM_LPOCLKS_RTCCLKSEL_SHIFT);
}


/*!
 * @brief Set the clock selection of LPOCLKSEL.
 *
 * This function sets the clock selection of LPOCLKSEL.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] setting The value to set.
 * @note This function ignores initialize member
 */
  void SIM_SetLpoClocks(SIM_Type* base, bool enableLpo1k, bool enableLpo32k, uint32_t sourceLpoClk, uint32_t sourceRtcClk)
{
    uint32_t regValue = base->LPOCLKS;

    regValue &= ~( SIM_LPOCLKS_LPO1KCLKEN_MASK  |
                   SIM_LPOCLKS_LPO32KCLKEN_MASK |
                   SIM_LPOCLKS_LPOCLKSEL_MASK   |
                   SIM_LPOCLKS_RTCCLKSEL_MASK   );

    regValue |= SIM_LPOCLKS_LPO1KCLKEN(enableLpo1k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPO32KCLKEN(enableLpo32k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPOCLKSEL(sourceLpoClk);
    regValue |= SIM_LPOCLKS_RTCCLKSEL(sourceRtcClk);

    /* Write value to register. */
    base->LPOCLKS = regValue;
}

/*!
 * @brief Set the EIM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the EIM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] EIM clock gate enable setting
 */
  void SIM_SetEimClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCEIM_MASK));
    regValue |= SIM_PLATCGC_CGCEIM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the EIM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the EIM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return EIM Clock Gating
 */
  bool SIM_GetEimClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCEIM_MASK) >> SIM_PLATCGC_CGCEIM_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Set the ERM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the ERM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable ERM clock gate enable setting
 */
  void SIM_SetErmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCERM_MASK));
    regValue |= SIM_PLATCGC_CGCERM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



/*!
 * @brief Gets the ERM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the ERM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return ERM Clock Gating
 */
  bool SIM_GetErmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCERM_MASK) >> SIM_PLATCGC_CGCERM_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Set the DMA Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the DMA Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable DMA clock gate enable setting
 */
  void SIM_SetDmaClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCDMA_MASK));
    regValue |= SIM_PLATCGC_CGCDMA(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



/*!
 * @brief Gets the DMA Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the DMA Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return DMA Clock Gating
 */
  bool SIM_GetDmaClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCDMA_MASK) >> SIM_PLATCGC_CGCDMA_SHIFT;
    return (regValue != 0U) ? true : false;
}


/*!
 * @brief Configure the MPU Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function configures the MPU Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable MPU clock gate enable setting
 */
  void SIM_SetMpuClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMPU_MASK));
    regValue |= SIM_PLATCGC_CGCMPU(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the MPU Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function gets the MPU Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return MPU Clock Gating
 */
  bool SIM_GetMpuClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMPU_MASK) >> SIM_PLATCGC_CGCMPU_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Configure the MSCM Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function configures the MSCM Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable MPU clock gate enable setting
 */
  void SIM_SetMscmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMSCM_MASK));
    regValue |= SIM_PLATCGC_CGCMSCM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the MSCM Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function gets the MSCM Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return MSCM Clock Gating
 */
  bool SIM_GetMscmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMSCM_MASK) >> SIM_PLATCGC_CGCMSCM_SHIFT;
    return (regValue != 0U) ? true : false;
}

#if defined(QuadSPI_INSTANCE_COUNT)
/*!
 * @brief Configure the QuadSPI Internal Reference Clock Gating
 *
 * This function configures the QuadSPI Internal Reference Clock Gating.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] configures QuadSPI Internal Reference Clock Gating
 */
  void SIM_SetQspiIntRefClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->MISCTRL0;
    regValue &= (uint32_t)(~(SIM_MISCTRL0_QSPI_CLK_SEL_MASK));
    regValue |= SIM_MISCTRL0_QSPI_CLK_SEL(enable ? 1UL : 0UL);
    base->MISCTRL0 = (uint32_t)regValue;
}

/*
 * @brief Get the current QSPI clocking mode selection
 *
 * This function gets the current QSPI clocking mode selection.
 *
 * @param[in] baseAddr Base address for current QSPI instance.
 * @return clocking mode selection
 */
  bool QSPI_GetClockingModeSelection(const QuadSPI_Type *baseAddr)
{
    return ((baseAddr->MCR & QuadSPI_MCR_SCLKCFG_MASK) >> QuadSPI_MCR_SCLKCFG_SHIFT) != 0U;
}

/*
 * @brief Get the current SIM clocking mode selection
 *
 * This function gets the current SIM clocking mode selection.
 *
 * @param[in] baseAddr Base address for current SIM instance.
 * @return clocking mode selection
 */
  bool SIM_GetClockingModeSelection(const SIM_Type *baseAddr)
{
    return ((baseAddr->MISCTRL0 & SIM_MISCTRL0_QSPI_CLK_SEL_MASK) >> SIM_MISCTRL0_QSPI_CLK_SEL_SHIFT) != 0U;
}

/*
 * @brief Get the clocking programmable divider
 *
 * This function gets the clocking programmable divider.
 *
 * @param[in] baseAddr Base address for current QSPI instance.
 * @return clocking programmable divider
 */
  uint32_t QSPI_GetClockingProgrammableDividerValue(const QuadSPI_Type *baseAddr)
{
    return (baseAddr->SOCCR & QuadSPI_SOCCR_SOCCFG_MASK) >> QuadSPI_SOCCR_SOCCFG_SHIFT;
}
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm0ExternalClkPinMode
 * Description   : Get FlexTimer 0 external clock pin select setting
 * This function will get FlexTimer 0 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm0ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM0CLKSEL_MASK) >> SIM_FTMOPT0_FTM0CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm1ExternalClkPinMode
 * Description   : Get FlexTimer 1 external clock pin select setting
 * This function will get FlexTimer 1 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm1ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM1CLKSEL_MASK) >> SIM_FTMOPT0_FTM1CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm2ExternalClkPinMode
 * Description   : Get FlexTimer 2 external clock pin select setting
 * This function will get FlexTimer 2 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm2ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM2CLKSEL_MASK) >> SIM_FTMOPT0_FTM2CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm3ExternalClkPinMode
 * Description   : Get FlexTimer 3 external clock pin select setting
 * This function will get FlexTimer 3 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm3ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM3CLKSEL_MASK) >> SIM_FTMOPT0_FTM3CLKSEL_SHIFT;
}

#if FTM_INSTANCE_COUNT > 4U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm4ExternalClkPinMode
 * Description   : Get FlexTimer 4 external clock pin select setting
 * This function will get FlexTimer 4 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm4ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM4CLKSEL_MASK) >> SIM_FTMOPT0_FTM4CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 5U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm5ExternalClkPinMode
 * Description   : Get FlexTimer 5 external clock pin select setting
 * This function will get FlexTimer 5 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm5ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM5CLKSEL_MASK) >> SIM_FTMOPT0_FTM5CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 6U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm6ExternalClkPinMode
 * Description   : Get FlexTimer 6 external clock pin select setting
 * This function will get FlexTimer 6 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm6ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM6CLKSEL_MASK) >> SIM_FTMOPT0_FTM6CLKSEL_SHIFT;
}
#endif


#if FTM_INSTANCE_COUNT > 7U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm7ExternalClkPinMode
 * Description   : Get FlexTimer 7 external clock pin select setting
 * This function will get FlexTimer 7 external clock pin select setting.
 *END**************************************************************************/
  uint32_t SIM_GetFtm7ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM7CLKSEL_MASK) >> SIM_FTMOPT0_FTM7CLKSEL_SHIFT;
}
#endif

/*FUNCTION*********************************************************************
 *
 * Function Name : SIM_GetLpo32KStatus
 * Description   : Get SIM LPO 32KHz clock gating status (LPO_32K_CLOCK).
 *END*************************************************************************/
  bool SIM_GetLpo32KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO32KCLKEN_MASK) >> SIM_LPOCLKS_LPO32KCLKEN_SHIFT) != 0U) ? true : false;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SIM_GetLpo1KStatus
 * Description   : Get SIM LPO 1KHz clock gating status (LPO_1K_CLOCK).
 *END*************************************************************************/
  bool SIM_GetLpo1KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO1KCLKEN_MASK) >> SIM_LPOCLKS_LPO1KCLKEN_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets the LPO selector value
 *
 * This function gets the LPO selector value
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout status
 */
  uint32_t SIM_GetLpoClkSelectorValue(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_LPOCLKSEL_MASK) >> SIM_LPOCLKS_LPOCLKSEL_SHIFT);
}

/*!
 * @brief Gets the clock out status
 *
 * This function gets the clock out status (enabled or disabled)
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout status
 */
  bool SIM_GetClockoutStatus(const SIM_Type * base)
{
    return (((base->CHIPCTL & SIM_CHIPCTL_CLKOUTEN_MASK) >> SIM_CHIPCTL_CLKOUTEN_SHIFT) == 0U) ? false : true;
}

/*!
 * @brief Gets the clock out divider value
 *
 * This function gets the clock out divider value
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout divider
 */
  uint32_t SIM_GetClockoutDividerValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTDIV_MASK) >> SIM_CHIPCTL_CLKOUTDIV_SHIFT);
}

/*!
 * @brief Gets the clock out source
 *
 * This function gets the clock out source
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout source
 */
  uint32_t SIM_GetClockoutSelectorValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTSEL_MASK) >> SIM_CHIPCTL_CLKOUTSEL_SHIFT);
}

/*!
 * @brief Sets ext pin clock source for FTM
 *
 * @param[in] base        sim base pointer
 * @param[in] instance    ftm instance
 * @param[in] source      clock source
 */
  void SIM_SetExtPinSourceFtm(SIM_Type* base, uint8_t instance, uint32_t source)
{
    uint32_t regValue = base->FTMOPT0;

    switch (instance)
    {
        case 0U:
            regValue &= ~SIM_FTMOPT0_FTM0CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM0CLKSEL(source);
            break;
        case 1U:
            regValue &= ~SIM_FTMOPT0_FTM1CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM1CLKSEL(source);
            break;
#if FTM_INSTANCE_COUNT > 2U
        case 2U:
            regValue &= ~SIM_FTMOPT0_FTM2CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM2CLKSEL(source);
            break;
#endif
#if FTM_INSTANCE_COUNT > 3U
        case 3U:
            regValue &= ~SIM_FTMOPT0_FTM3CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM3CLKSEL(source);
            break;
#endif
#if FTM_INSTANCE_COUNT > 4U
        case 4U:
            regValue &= ~SIM_FTMOPT0_FTM4CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM4CLKSEL(source);
            break;
#endif
#if FTM_INSTANCE_COUNT > 5U
        case 5U:
            regValue &= ~SIM_FTMOPT0_FTM5CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM5CLKSEL(source);
            break;
#endif
#if FTM_INSTANCE_COUNT > 6U
        case 6U:
            regValue &= ~SIM_FTMOPT0_FTM6CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM6CLKSEL(source);
            break;
#endif
#if FTM_INSTANCE_COUNT > 7U
        case 7U:
            regValue &= ~SIM_FTMOPT0_FTM7CLKSEL_MASK;
            regValue |= SIM_FTMOPT0_FTM7CLKSEL(source);
            break;
#endif
        default:
            /* Do nothing */
            break;
    }

    base->FTMOPT0 = regValue;
}

/*!
 * @brief Sets clockout
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock source
 * @param[in] divider     clock divider
 */
  void SIM_SetClockout(SIM_Type* base, bool enable, uint32_t source, uint32_t divider)
{
    uint32_t regValue;

    /* CLKOUTEN should be first cleared and then execute sequence */
    base->CHIPCTL &= ~SIM_CHIPCTL_CLKOUTEN_MASK;

    regValue = base->CHIPCTL;
    regValue &= ~( SIM_CHIPCTL_CLKOUTEN_MASK  |
                   SIM_CHIPCTL_CLKOUTDIV_MASK |
                   SIM_CHIPCTL_CLKOUTSEL_MASK );

    regValue |= SIM_CHIPCTL_CLKOUTEN(enable ? 1UL : 0UL);
    regValue |= SIM_CHIPCTL_CLKOUTSEL(source);
    regValue |= SIM_CHIPCTL_CLKOUTDIV(divider);

    base->CHIPCTL = regValue;
}

/*!
 * @brief Configure clock trace source
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock trace source
 */
  void SIM_SetTraceClockSource(SIM_Type* base, uint32_t clTraceSrc)
{
    uint32_t regValue;

    /* Configure trace source. */
    regValue = (uint32_t)base->CHIPCTL;
    regValue &= (uint32_t)(~(SIM_CHIPCTL_TRACECLK_SEL_MASK));
    regValue |= SIM_CHIPCTL_TRACECLK_SEL(clTraceSrc);
    base->CHIPCTL = (uint32_t)regValue;
}

/*!
 * @brief Clears SIM Debug Trace configuration.
 *
 * This function disables the SIM Debug Trace clock.
 *
 * @param[in] base Register base address for the SIM instance.
 */
  void SIM_ClearTraceClockConfig(SIM_Type * base)
{
    /* Disable divider. */
    base->CLKDIV4 &= 0U;
}

/*!
 * @brief Set SIM Debug Trace configuration.
 *
 * This function disables the SIM Debug Trace clock.
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock trace source
 */
  void SIM_SetTraceClockConfig(SIM_Type * base, bool enable, uint32_t divider, uint32_t multiplier)
{
    base->CLKDIV4 = SIM_CLKDIV4_TRACEDIVEN(enable ? 1UL : 0UL) |
                    SIM_CLKDIV4_TRACEDIV(divider)              |
                    SIM_CLKDIV4_TRACEFRAC(multiplier);
}


#if 1
/*!
 * @brief Gets spll system clock mode status
 *
 * This function checks whether SPLL is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll system clock mode status
 *        - false : SPLL is not the system clock source
 *        - true : SPLL is the system clock source
 */
 bool SCG_GetSpllSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SPLLCSR;
    regValue = (regValue & SCG_SPLLCSR_SPLLSEL_MASK) >> SCG_SPLLCSR_SPLLSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets spll clock status
 * This function checks whether SPLL is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll  clock status
 *        - false : SPLL is not enabled or clock is not valid
 *        - true  : SPLL is enabled and clock is valid
 */
 bool SCG_GetSpllStatus(const SCG_Type* const base)
{
    return (((base->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK) >> SCG_SPLLCSR_SPLLVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets spll predivider
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll predivider value
 */
uint32_t SCG_GetSpllPredivider(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT);
}

/*!
 * @brief Gets spll multiplier
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll multiplier value
 */
 uint32_t SCG_GetSpllMultiplier(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT);
}

/*!
 * @brief Clears SPLL lock register
 *
 * This function clears SPLL lock.
 *
 * @param[in] base        scg base pointer
 *
 */
 void SCG_ClearSpllLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SPLLCSR &= (uint32_t)(~(SCG_SPLLCSR_LK_MASK));
}


/*!
 * @brief Clears SPLL control register
 *
 * @param[in] base        scg base pointer
 *
 */
static  void SCG_ClearSpllControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->SPLLCSR = SCG_SPLLCSR_SPLLERR_MASK;
}

/*!
 * @brief Sets SPLL configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] divider     spll predivider value
 * @param[in] multiplier  spll multiplier value
 */
  void SCG_SetSpllConfiguration(SCG_Type* base, uint8_t divider, uint8_t multiplier)
{
    /* Set PLL configuration. */
    base->SPLLCFG = SCG_SPLLCFG_PREDIV(divider)  |
                    SCG_SPLLCFG_MULT(multiplier);
}

/*!
 * @brief Sets SPLL control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] resetMode   clock monitor reset enablement
 * @param[in] lockMode    control register can be written or not
 */
 void SCG_SetSpllControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SPLLCSR_SPLLEN(1U)                        |
                     SCG_SPLLCSR_SPLLCM((monitorMode) ? 1UL : 0UL) |
                     SCG_SPLLCSR_SPLLCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SPLLCSR_LK((lockMode) ? 1UL : 0UL);

    base->SPLLCSR = value;
}
#endif



