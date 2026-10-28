
#ifndef __CLOCK_HW_ACCESS_H__
#define __CLOCK_HW_ACCESS_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file pcc_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * This is required to implement enumeration entries as macro.
 * Enumeration entries (macros) are referenced from application code.
 */

/*!
 * @ingroup pcc_hw_access
 * @defgroup pcc_hw_access
 * @{
 */


/*! @brief Clock name mappings
 *         Constant array storing the mappings between clock names and peripheral clock control indexes.
 *         If there is no peripheral clock control index for a clock name, then the corresponding value is
 *         PCC_INVALID_INDEX.
 */
extern const uint16_t clockNameMappings[CLOCK_NAME_COUNT];





 void PCC_SetPeripheralClockControl(PCC_Type* base, clock_names_t clockName, 
bool clockGate, uint32_t clockSource, uint32_t divider, uint32_t multiplier);


 void PCC_SetClockMode(PCC_Type* const base,
                                       const clock_names_t clockName,
                                       const bool isClockEnabled);




 bool PCC_GetClockMode(const PCC_Type* const base,
                                       const clock_names_t clockName);


 uint32_t PCC_GetClockSourceSel(const PCC_Type* const base,
                                                                 const 
clock_names_t clockName);


 uint32_t PCC_GetFracValueSel(const PCC_Type* const base,
                                               const clock_names_t clockName);


 uint32_t PCC_GetDividerSel(const PCC_Type* const base,
                                             const clock_names_t clockName);

uint32_t SMC_GetCurrentRunningMode(const SMC_Type* const baseAddr);



  uint32_t SCG_GetClockoutSourceSel(const SCG_Type * base);



  uint32_t SCG_GetCurrentSystemClockSource(const SCG_Type * base);


  uint32_t SCG_GetCurrentCoreClockDividerRatio(const SCG_Type * base);


  uint32_t SCG_GetCurrentBusClockDividerRatio(const SCG_Type * base);


  uint32_t SCG_GetCurrentSlowClockDividerRatio(const SCG_Type * base);


  void SCG_SetRunClockControl(SCG_Type * base, uint32_t source, uint32_t 
coreDivider, uint32_t busDivider, uint32_t slowDivider);


  void SCG_SetVlprClockControl(SCG_Type * base, uint32_t source, uint32_t 
coreDivider, uint32_t busDivider, uint32_t slowDivider);


  uint32_t SCG_GetFircFirstAsyncDivider(const SCG_Type * base);


  uint32_t SCG_GetFircSecondAsyncDivider(const SCG_Type * base);



  void SCG_SetFircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2);



  uint32_t SCG_GetSircFirstAsyncDivider(const SCG_Type * base);


  uint32_t SCG_GetSircSecondAsyncDivider(const SCG_Type * base);



  void SCG_SetSircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2);




  uint32_t SCG_GetSoscFirstAsyncDivider(const SCG_Type * base);


  uint32_t SCG_GetSoscSecondAsyncDivider(const SCG_Type * base);



  void SCG_SetSoscAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2);

#if FEATURE_HAS_SPLL_CLK
#ifdef SCG_SPLLCFG_SOURCE_MASK

  uint32_t SCG_GetSourcSpll(const SCG_Type * base);

  void SCG_SetSourceSpll(SCG_Type * base, uint32_t source);
#endif

  uint32_t SCG_GetSpllFirstAsyncDivider(const SCG_Type * base);


  uint32_t SCG_GetSpllSecondAsyncDivider(const SCG_Type * base);



  void SCG_SetSpllAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2);
#endif


  void SCG_SetClockoutSourceSel(SCG_Type * base, uint32_t source);


  bool SCG_GetSircSystemClockMode(const SCG_Type* const base);


  bool SCG_GetSircStatus(const SCG_Type* const base);


  uint32_t SCG_GetSircRange(const SCG_Type* const base);


  void SCG_ClearSircLock(SCG_Type*  base);



  void SCG_ClearSircControl(SCG_Type* base);



  void SCG_SetSircConfiguration(SCG_Type* base, uint8_t range);


  void SCG_SetSircControl(SCG_Type* base, bool enableInStop, bool 
enableInLowPower, bool lockMode);



  bool SCG_GetFircSystemClockMode(const SCG_Type* const base);


  bool SCG_GetFircStatus(const SCG_Type* const base);


  uint32_t SCG_GetFircRange(const SCG_Type* const base);


  void SCG_ClearFircLock(SCG_Type*  base);



  void SCG_ClearFircControl(SCG_Type* base);



  void SCG_SetFircConfiguration(SCG_Type* base, uint8_t range);


  void SCG_SetFircControl(SCG_Type* base, bool regulator, bool lockMode);



  bool SCG_GetSoscSystemClockMode(const SCG_Type* const base);


  bool SCG_GetSoscStatus(const SCG_Type* const base);


  void SCG_ClearSoscLock(SCG_Type*  base);



  void SCG_ClearSoscControl(SCG_Type* base);





  void SCG_SetSoscConfiguration(SCG_Type* base, uint32_t range, uint32_t gain, uint32_t extRef);


  void SCG_SetSoscControl(SCG_Type* base, bool monitorMode, bool resetMode, 
bool lockMode);


  void PMC_SetLpoMode(PMC_Type* const baseAddr, const bool enable);


  bool PMC_GetLpoMode(const PMC_Type * const baseAddr);



  void PMC_SetLpoTrimValue(PMC_Type* const baseAddr, const int8_t decimalValue
);



  uint32_t SIM_GetRtcClkSrc(const SIM_Type * base);



  void SIM_SetLpoClocks(SIM_Type* base, bool enableLpo1k, bool enableLpo32k, 
uint32_t sourceLpoClk, uint32_t sourceRtcClk);


  void SIM_SetEimClockGate(SIM_Type* base, bool enable);


  bool SIM_GetEimClockGate(const SIM_Type * base);


  void SIM_SetErmClockGate(SIM_Type* base, bool enable);




  bool SIM_GetErmClockGate(const SIM_Type * base);


  void SIM_SetDmaClockGate(SIM_Type* base, bool enable);




  bool SIM_GetDmaClockGate(const SIM_Type * base);



  void SIM_SetMpuClockGate(SIM_Type* base, bool enable);


  bool SIM_GetMpuClockGate(const SIM_Type * base);


  void SIM_SetMscmClockGate(SIM_Type* base, bool enable);


  bool SIM_GetMscmClockGate(const SIM_Type * base);

#if defined(QuadSPI_INSTANCE_COUNT)
  void SIM_SetQspiIntRefClockGate(SIM_Type* base, bool enable);


  bool QSPI_GetClockingModeSelection(const QuadSPI_Type *baseAddr);


  bool SIM_GetClockingModeSelection(const SIM_Type *baseAddr);


  uint32_t QSPI_GetClockingProgrammableDividerValue(const QuadSPI_Type *
baseAddr);
#endif



  uint32_t SIM_GetFtm0ExternalClkPinMode(const SIM_Type * base);


  uint32_t SIM_GetFtm1ExternalClkPinMode(const SIM_Type * base);


  uint32_t SIM_GetFtm2ExternalClkPinMode(const SIM_Type * base);


  uint32_t SIM_GetFtm3ExternalClkPinMode(const SIM_Type * base);

#if FTM_INSTANCE_COUNT > 4U

  uint32_t SIM_GetFtm4ExternalClkPinMode(const SIM_Type * base);
#endif

#if FTM_INSTANCE_COUNT > 5U

  uint32_t SIM_GetFtm5ExternalClkPinMode(const SIM_Type * base);
#endif

#if FTM_INSTANCE_COUNT > 6U

  uint32_t SIM_GetFtm6ExternalClkPinMode(const SIM_Type * base);
#endif


#if FTM_INSTANCE_COUNT > 7U

  uint32_t SIM_GetFtm7ExternalClkPinMode(const SIM_Type * base);
#endif


  bool SIM_GetLpo32KStatus(const SIM_Type * base);


  bool SIM_GetLpo1KStatus(const SIM_Type * base);


  uint32_t SIM_GetLpoClkSelectorValue(const SIM_Type * base);


  bool SIM_GetClockoutStatus(const SIM_Type * base);


  uint32_t SIM_GetClockoutDividerValue(const SIM_Type * base);


  uint32_t SIM_GetClockoutSelectorValue(const SIM_Type * base);


  void SIM_SetExtPinSourceFtm(SIM_Type* base, uint8_t instance, uint32_t 
source);


  void SIM_SetClockout(SIM_Type* base, bool enable, uint32_t source, uint32_t 
divider);


  void SIM_SetTraceClockSource(SIM_Type* base, uint32_t clTraceSrc);


  void SIM_ClearTraceClockConfig(SIM_Type * base);


  void SIM_SetTraceClockConfig(SIM_Type * base, bool enable, uint32_t divider
, uint32_t multiplier);



 bool SCG_GetSpllSystemClockMode(const SCG_Type* const base);

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
 bool SCG_GetSpllStatus(const SCG_Type* const base);
/*!
 * @brief Gets spll predivider
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll predivider value
 */
uint32_t SCG_GetSpllPredivider(const SCG_Type* const base);

/*!
 * @brief Gets spll multiplier
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll multiplier value
 */
 uint32_t SCG_GetSpllMultiplier(const SCG_Type* const base);

/*!
 * @brief Clears SPLL lock register
 *
 * This function clears SPLL lock.
 *
 * @param[in] base        scg base pointer
 *
 */
 void SCG_ClearSpllLock(SCG_Type*  base);


/*!
 * @brief Clears SPLL control register
 *
 * @param[in] base        scg base pointer
 *
 */
static  void SCG_ClearSpllControl(SCG_Type* base);

/*!
 * @brief Sets SPLL configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] divider     spll predivider value
 * @param[in] multiplier  spll multiplier value
 */
  void SCG_SetSpllConfiguration(SCG_Type* base, uint8_t divider, uint8_t multiplier);
/*!
 * @brief Sets SPLL control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] resetMode   clock monitor reset enablement
 * @param[in] lockMode    control register can be written or not
 */
 void SCG_SetSpllControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode);


#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* PCC_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
