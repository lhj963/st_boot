/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
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
#include "flexio_hw_access.h"



/*
 * This function returns the number of shifters of the FlexIO module
 */
  uint8_t FLEXIO_GetShifterNum(const FLEXIO_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PARAM;
    tmp = (tmp & FLEXIO_PARAM_SHIFTER_MASK) >> FLEXIO_PARAM_SHIFTER_SHIFT;
    return (uint8_t)tmp;
}


/*
 * This function enables of disables FlexIO functionality in debug mode.
 */
  void FLEXIO_SetDebugMode(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_DBGE_MASK));
    regValue |= FLEXIO_CTRL_DBGE(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


/*
 * Calling this function with enable parameter set to true resets all internal
 * master logic and registers, except the FlexIO Control Register. The reset state
 * persists until this function is called with enable parameter set to false.
 */
  void FLEXIO_SetSoftwareReset(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_SWRST_MASK));
    regValue |= FLEXIO_CTRL_SWRST(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


/*
 * This function enables or disables the FlexIO module.
 */
  void FLEXIO_SetEnable(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_FLEXEN_MASK));
    regValue |= FLEXIO_CTRL_FLEXEN(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


/*
 * This function returns the data read from all the FLEXIO pins. Only the lower
 * n bits are valid, where n is the number of pins returned by FLEXIO_GetPinNum().
 */
  uint8_t FLEXIO_GetPinData(const FLEXIO_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PIN;
    tmp = (tmp & FLEXIO_PIN_PDI_MASK) >> FLEXIO_PIN_PDI_SHIFT;
    return (uint8_t)tmp;
}


/*
 * This function returns the value of the status flag for the specified shifter.
 * The meaning of the status flag depends on the current mode.
 *  - Transmit mode: shifter buffer is empty and ready to accept more data
 *  - Receive mode: shifter buffer is full and received data can be read from it
 *  - Match Store mode: match occurred between shifter buffer and shifter
 *  - Match Continuous mode: current match result between shifter buffer and shifter
 */
  bool FLEXIO_GetShifterStatus(const FLEXIO_Type *baseAddr, uint8_t shifter)
{
    uint32_t regValue = (uint32_t)baseAddr->SHIFTSTAT;
    regValue = (regValue >> shifter) & 1U;
    return (bool)regValue;
}


/*
 * This function returns the value of the status flags for all shifters. Each bit in 
 * the returned value specifies the status for one shifter, starting with 
 * shifter 0 from least significant bit.
 * The meaning of the status flag depends on the current mode.
 *  - Transmit mode: shifter buffer is empty and ready to accept more data
 *  - Receive mode: shifter buffer is full and received data can be read from it
 *  - Match Store mode: match occurred between shifter buffer and shifter
 *  - Match Continuous mode: current match result between shifter buffer and shifter
 */
  uint32_t FLEXIO_GetAllShifterStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTSTAT;
}


/*
 * This function clears the status flag for the specified shifter. This is possible in
 * all modes except Match Continuous mode.
 */
  void FLEXIO_ClearShifterStatus(FLEXIO_Type *baseAddr, uint8_t shifter)
{
    baseAddr->SHIFTSTAT = 1UL << shifter;
}


/*
 * This function returns the value of the error status flag for the specified shifter.
 * The meaning of the error status flag depends on the current mode.
 *  - Transmit mode: shifter buffer was not written before it was transferred in the shifter (buffer overrun)
 *  - Receive mode: shifter buffer was not read before new data was transferred from the shifter (buffer underrun)
 *  - Match Store mode: match event occurred before the previous match data was read from shifter buffer (buffer overrun)
 *  - Match Continuous mode: match occurred between shifter buffer and shifter
 */
  bool FLEXIO_GetShifterErrorStatus(const FLEXIO_Type *baseAddr, uint8_t shifter)
{
    uint32_t regValue = (uint32_t)baseAddr->SHIFTERR;
    regValue = (regValue >> shifter) & 1U;
    return (bool)regValue;
}


/*
 * This function returns the value of the error status flags for all shifters. Each bit in 
 * the returned value specifies the error status for one shifter, starting with 
 * shifter 0 from least significant bit.
 * The meaning of the error status flag depends on the current mode.
 *  - Transmit mode: shifter buffer was not written before it was transferred in the shifter (buffer overrun)
 *  - Receive mode: shifter buffer was not read before new data was transferred from the shifter (buffer underrun)
 *  - Match Store mode: match event occurred before the previous match data was read from shifter buffer (buffer overrun)
 *  - Match Continuous mode: match occurred between shifter buffer and shifter
 */
  uint32_t FLEXIO_GetAllShifterErrorStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTERR;
}


/*
 * This function clears the error status flag for the specified shifter.
 */
  void FLEXIO_ClearShifterErrorStatus(FLEXIO_Type *baseAddr, uint8_t shifter)
{
    baseAddr->SHIFTERR = 1UL << shifter;
}


/*
 * This function returns the value of the status flag for the specified timer.
 * The meaning of the status flag depends on the current mode.
 *  - 8-bit counter mode: the timer status flag is set when the upper 8-bit counter equals zero
 * and decrements. This also causes the counter to reload with the value in the compare register.
 *  - 8-bit PWM mode: the upper 8-bit counter equals zero and decrements. This also causes the
 * counter to reload with the value in the compare register.
 *  - 16-bit counter mode: the 16-bit counter equals zero and decrements. This also causes the
 * counter to reload with the value in the compare register.
 */
  bool FLEXIO_GetTimerStatus(const FLEXIO_Type *baseAddr, uint8_t timer)
{
    uint32_t regValue = (uint32_t)baseAddr->TIMSTAT;
    regValue = (regValue >> timer) & 1U;
    return (bool)regValue;
}


/*
 * This function returns the value of the status flags for all timers. Each bit in 
 * the returned value specifies the status for one timer, starting with 
 * timer 0 from least significant bit.
 * The meaning of the status flag depends on the current mode.
 *  - 8-bit counter mode: the timer status flag is set when the upper 8-bit counter equals zero
 * and decrements. This also causes the counter to reload with the value in the compare register.
 *  - 8-bit PWM mode: the upper 8-bit counter equals zero and decrements. This also causes the
 * counter to reload with the value in the compare register.
 *  - 16-bit counter mode: the 16-bit counter equals zero and decrements. This also causes the
 * counter to reload with the value in the compare register.
 */
  uint32_t FLEXIO_GetAllTimerStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->TIMSTAT;
}


/*
 * This function clears the status flag for the specified timer.
 */
  void FLEXIO_ClearTimerStatus(FLEXIO_Type *baseAddr, uint8_t timer)
{
    baseAddr->TIMSTAT = 1UL << timer;
}


/*
 * Returns the state of the interrupt for all shifters. Each bit in 
 * the returned value specifies the interrupt state for one shifter, starting with 
 * shifter 0 from least significant bit.
 */
  uint32_t FLEXIO_GetAllShifterInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTSIEN;
}


/*
 * Enable or disable specified shifter interrupts. The interrupt mask must contain a
 * bit of 1 for each shifter who's interrupt must be enabled or disabled.
 */
  void FLEXIO_SetShifterInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTSIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->SHIFTSIEN = tmp;
}



/*
 * Returns the state of the error interrupt for all shifters. Each bit in 
 * the returned value specifies the interrupt state for one shifter, starting with 
 * shifter 0 from least significant bit.
 */
  uint32_t FLEXIO_GetAllShifterErrorInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTEIEN;
}


/*
 * Enable or disable specified shifter error interrupts. The interrupt mask must contain a
 * bit of 1 for each shifter who's error interrupt must be enabled or disabled.
 */
  void FLEXIO_SetShifterErrorInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTEIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->SHIFTEIEN = tmp;
}


/*
 * Returns the state of the interrupt for all timers. Each bit in 
 * the returned value specifies the interrupt state for one timer, starting with 
 * timer 0 from least significant bit.
 */
  uint32_t FLEXIO_GetAllTimerInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->TIMIEN;
}


/*
 * Enable or disable specified timer interrupts. The interrupt mask must contain a
 * bit of 1 for each timer who's interrupt must be enabled or disabled.
 */
  void FLEXIO_SetTimerInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->TIMIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->TIMIEN = tmp;
}


/*
 * Enable or disable specified shifter DMA requests. The request mask must contain a
 * bit of 1 for each shifter who's DMA requests must be enabled or disabled.
 */
  void FLEXIO_SetShifterDMARequest(FLEXIO_Type *baseAddr, uint8_t requestMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTSDEN;

    if (enable == true)
    {
        tmp |= requestMask;
    }
    else
    {
        tmp &= ~requestMask;
    }
    baseAddr->SHIFTSDEN = tmp;
}


/*
 * This function assigns a timer to control the specified shifter, and also configures its polarity.
 */
  void FLEXIO_SetShifterTimer(FLEXIO_Type *baseAddr,
                                              uint8_t shifter,
                                              uint8_t timer,
                                              flexio_timer_polarity_t polarity)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_TIMSEL_MASK);
    tmp |= FLEXIO_SHIFTCTL_TIMSEL(timer);
    tmp &= ~(FLEXIO_SHIFTCTL_TIMPOL_MASK);
    tmp |= FLEXIO_SHIFTCTL_TIMPOL(polarity);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


/*
 * This function assigns the specified pin to the specified shifter, and also sets
 * its polarity and configuration.
 */
  void FLEXIO_SetShifterPin(FLEXIO_Type *baseAddr,
                                            uint8_t shifter,
                                            uint8_t pin,
                                            flexio_pin_polarity_t polarity,
                                            flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_PINSEL_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINSEL(pin);
    tmp &= ~(FLEXIO_SHIFTCTL_PINPOL_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINPOL(polarity);
    tmp &= ~(FLEXIO_SHIFTCTL_PINCFG_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINCFG(config);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


/*
 * This function configures the pin assigned to the specified specified shifter. 
 * It does not change the other pin-related settings.
 */
  void FLEXIO_SetShifterPinConfig(FLEXIO_Type *baseAddr,
                                                  uint8_t shifter,
                                                  flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_PINCFG_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINCFG(config);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


/*
 * This function configures the mode for the specified shifter.
 */
  void FLEXIO_SetShifterMode(FLEXIO_Type *baseAddr,
                                             uint8_t shifter,
                                             flexio_shifter_mode_t mode)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_SMOD_MASK);
    tmp |= FLEXIO_SHIFTCTL_SMOD(mode);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


/*
 * This function configures the control settings for the specified shifter: mode settings, 
 * pin settings and timer settings.
 */
  void FLEXIO_SetShifterControl(FLEXIO_Type *baseAddr,
                                                uint8_t shifter,
                                                flexio_shifter_mode_t mode,
                                                uint8_t pin,
                                                flexio_pin_polarity_t pinPolarity,
                                                flexio_pin_config_t pinConfig,
                                                uint8_t timer,
                                                flexio_timer_polarity_t timerPolarity)
{
    baseAddr->SHIFTCTL[shifter] = FLEXIO_SHIFTCTL_SMOD(mode)
                                | FLEXIO_SHIFTCTL_PINPOL(pinPolarity)
                                | FLEXIO_SHIFTCTL_PINSEL(pin)
                                | FLEXIO_SHIFTCTL_PINCFG(pinConfig)
                                | FLEXIO_SHIFTCTL_TIMPOL(timerPolarity)
                                | FLEXIO_SHIFTCTL_TIMSEL(timer);
}


/*
 * This function configures the input source of the specified shifter.
 */
  void FLEXIO_SetShifterInputSource(FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_source_t source)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_INSRC_MASK);
    tmp |= FLEXIO_SHIFTCFG_INSRC(source);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


/*
 * This function configures the sending or receiving of
 * a stop bit in Transmit, Receive or Match Store modes.
 */
  void FLEXIO_SetShifterStopBit(FLEXIO_Type *baseAddr, uint8_t shifter, flexio_shifter_stop_t stop)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_SSTOP_MASK);
    tmp |= FLEXIO_SHIFTCFG_SSTOP(stop);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


/*
 * This function configures the sending or receiving of
 * a start bit in Transmit, Receive or Match Store modes.
 */
  void FLEXIO_SetShifterStartBit(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 flexio_shifter_start_t start)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_SSTART_MASK);
    tmp |= FLEXIO_SHIFTCFG_SSTART(start);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


/*
 * This function sets the following configurations for the specified shifter:
 * start bit, stop bit, input source
 */
  void FLEXIO_SetShifterConfig(FLEXIO_Type *baseAddr,
                                               uint8_t shifter,
                                               flexio_shifter_start_t start,
                                               flexio_shifter_stop_t stop,
                                               flexio_shifter_source_t source)
{
    baseAddr->SHIFTCFG[shifter] = FLEXIO_SHIFTCFG_SSTART(start)
                                | FLEXIO_SHIFTCFG_SSTOP(stop)
                                | FLEXIO_SHIFTCFG_INSRC(source);
}


/*
 * This function reads data from the specified shifter buffer. The data can be
 * read in any of the four ways allowed by the hardware - see description of type
 * flexio_shifter_buffer_mode_t for details.
 */
  uint32_t FLEXIO_ReadShifterBuffer(const FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_buffer_mode_t mode)
{
    uint32_t data;

    switch (mode)
    {
        case FLEXIO_SHIFTER_RW_MODE_NORMAL:
            data = baseAddr->SHIFTBUF[shifter];
            break;
        case FLEXIO_SHIFTER_RW_MODE_BIT_SWAP:
            data = baseAddr->SHIFTBUFBIS[shifter];
            break;
        default:
            /* bad read mode */
            data = 0U;
            break;
    }
    return data;
}


/*
 * This function writes data in the specified shifter buffer. The data can be
 * written in any of the four ways allowed by the hardware - see description of type
 * flexio_shifter_buffer_mode_t for details.
 */
  void FLEXIO_WriteShifterBuffer(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 uint32_t value,
                                                 flexio_shifter_buffer_mode_t mode)
{
    switch (mode)
    {
        case FLEXIO_SHIFTER_RW_MODE_NORMAL:
            baseAddr->SHIFTBUF[shifter] = value;
            break;
        case FLEXIO_SHIFTER_RW_MODE_BIT_SWAP:
            baseAddr->SHIFTBUFBIS[shifter] = value;
            break;
        default:
            /* bad write mode */
            break;
    }
}


/*
 * This function configures the trigger for the specified timer, and also its
 * source (internal or external) and polarity settings.
 * For internal triggers, the selection is as follows:
 *  - 4*N - Pin 2*N input
 *  - 4*N+1 - Shifter N status flag
 *  - 4*N+2 - Pin 2*N+1 input
 *  - 4*N+3 - Timer N trigger output
 */
  void FLEXIO_SetTimerTrigger(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t trigger,
                                                 flexio_trigger_polarity_t polarity,
                                                 flexio_trigger_source_t source)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_TRGSEL_MASK);
    tmp |= FLEXIO_TIMCTL_TRGSEL(trigger);
    tmp &= ~(FLEXIO_TIMCTL_TRGPOL_MASK);
    tmp |= FLEXIO_TIMCTL_TRGPOL(polarity);
    tmp &= ~(FLEXIO_TIMCTL_TRGSRC_MASK);
    tmp |= FLEXIO_TIMCTL_TRGSRC(source);
    baseAddr->TIMCTL[timer] = tmp;
}


/*
 * This function assigns the specified pin to the specified timer, and also sets
 * its polarity and configuration.
 */
  void FLEXIO_SetTimerPin(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t pin,
                                                 flexio_pin_polarity_t polarity,
                                                 flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_PINSEL_MASK);
    tmp |= FLEXIO_TIMCTL_PINSEL(pin);
    tmp &= ~(FLEXIO_TIMCTL_PINPOL_MASK);
    tmp |= FLEXIO_TIMCTL_PINPOL(polarity);
    tmp &= ~(FLEXIO_TIMCTL_PINCFG_MASK);
    tmp |= FLEXIO_TIMCTL_PINCFG(config);
    baseAddr->TIMCTL[timer] = tmp;
}


/*
 * This function configures the mode for the specified timer.
 * In 8-bit counter mode, the lower 8-bits of the counter and compare register are used to
 * configure the baud rate of the timer shift clock and the upper 8-bits are used to configure
 * the shifter bit count.
 * In 8-bit PWM mode, the lower 8-bits of the counter and compare
 * register are used to configure the high period of the timer shift clock and the upper
 * 8-bits are used to configure the low period of the timer shift clock. The shifter bit count
 * is configured using another timer or external signal.
 * In 16-bit counter mode, the full 16-bits of the counter and compare register are used to
 * configure either the baud rate of the shift clock or the shifter bit count.
 */
  void FLEXIO_SetTimerMode(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_mode_t mode)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_TIMOD_MASK);
    tmp |= FLEXIO_TIMCTL_TIMOD(mode);
    baseAddr->TIMCTL[timer] = tmp;
}


/*
 * This function configures the control settings for the specified timer: mode settings, 
 * pin settings and trigger settings.
 */
  void FLEXIO_SetTimerControl(FLEXIO_Type *baseAddr,
                                              uint8_t timer,
                                              uint8_t trigger,
                                              flexio_trigger_polarity_t triggerPolarity,
                                              flexio_trigger_source_t triggerSource,
                                              uint8_t pin,
                                              flexio_pin_polarity_t pinPolarity,
                                              flexio_pin_config_t pinConfig,
                                              flexio_timer_mode_t mode)
{
    baseAddr->TIMCTL[timer] = FLEXIO_TIMCTL_TIMOD(mode)
                            | FLEXIO_TIMCTL_PINSEL(pin)
                            | FLEXIO_TIMCTL_PINPOL(pinPolarity)
                            | FLEXIO_TIMCTL_PINCFG(pinConfig)
                            | FLEXIO_TIMCTL_TRGSRC(triggerSource)
                            | FLEXIO_TIMCTL_TRGPOL(triggerPolarity)
                            | FLEXIO_TIMCTL_TRGSEL(trigger);
}


/*
 * This function configures the initial output of the specified timer and whether it is
 * affected by the Timer reset.
 */
  void FLEXIO_SetTimerInitialOutput(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_output_t output)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMOUT_MASK);
    tmp |= FLEXIO_TIMCFG_TIMOUT(output);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures the decrement condition for the specified timer and the source
 * of the shift clock.
 * See description of type flexio_timer_decrement_t for a list of options.
 */
  void FLEXIO_SetTimerDecrement(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_decrement_t decrement)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMDEC_MASK);
    tmp |= FLEXIO_TIMCFG_TIMDEC(decrement);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures the conditions that cause the timer counter (and optionally
 * output) to be reset. In 8-bit counter mode, the timer reset will only reset the
 * lower 8-bits that configure the baud rate. In all other modes, the timer reset
 * will reset the full 16-bits of the counter.
 * See description of type flexio_timer_decrement_t for a list of options.
 */
  void FLEXIO_SetTimerReset(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_reset_t reset)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMRST_MASK);
    tmp |= FLEXIO_TIMCFG_TIMRST(reset);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures the condition that cause the specified timer to be disabled.
 * See description of type flexio_timer_disable_t for a list of options.
 */
  void FLEXIO_SetTimerDisable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_disable_t disable)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMDIS_MASK);
    tmp |= FLEXIO_TIMCFG_TIMDIS(disable);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures the condition that cause the specified timer to be enabled
 * and start decrementing.
 * See description of type flexio_timer_disable_t for a list of options.
 */
  void FLEXIO_SetTimerEnable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_enable_t enable)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMENA_MASK);
    tmp |= FLEXIO_TIMCFG_TIMENA(enable);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures stop bit insertion for the specified timer.
 * The stop bit can be added on a timer compare (between each word) or on a timer disable.
 * When stop bit is enabled, configured shifters will output the contents of the stop bit
 * when the timer is disabled. When stop bit is enabled on timer disable, the timer remains
 * disabled until the next rising edge of the shift clock. If configured for both timer
 * compare and timer disable, only one stop bit is inserted on timer disable.
 */
  void FLEXIO_SetTimerStop(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_stop_t stop)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TSTOP_MASK);
    tmp |= FLEXIO_TIMCFG_TSTOP(stop);
    baseAddr->TIMCFG[timer] = tmp;
}


/*
 * This function configures start bit insertion for the specified timer.
 * When start bit is enabled, configured shifters will output the contents of the start
 * bit when the timer is enabled and the timer counter will reload from the compare
 * register on the first rising edge of the shift clock.
 */
  void FLEXIO_SetTimerStart(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start)
{
    uint32_t regValue = (uint32_t)baseAddr->TIMCFG[timer];
    regValue &= (uint32_t)(~(FLEXIO_TIMCFG_TSTART_MASK));
    regValue |= FLEXIO_TIMCFG_TSTART(start);
    baseAddr->TIMCFG[timer] = (uint32_t)regValue;
}


/*
 * This function sets the following configurations for the specified timer:
 * start bit, stop bit, enable condition, disable condition, reset condition, 
 * decrement condition, initial output
 */
  void FLEXIO_SetTimerConfig(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start,
                                             flexio_timer_stop_t stop,
                                             flexio_timer_enable_t enable,
                                             flexio_timer_disable_t disable,
                                             flexio_timer_reset_t reset,
                                             flexio_timer_decrement_t decrement,
                                             flexio_timer_output_t output)
{

    baseAddr->TIMCFG[timer] = FLEXIO_TIMCFG_TSTART(start)
                            | FLEXIO_TIMCFG_TSTOP(stop)
                            | FLEXIO_TIMCFG_TIMENA(enable)
                            | FLEXIO_TIMCFG_TIMDIS(disable)
                            | FLEXIO_TIMCFG_TIMRST(reset)
                            | FLEXIO_TIMCFG_TIMDEC(decrement)
                            | FLEXIO_TIMCFG_TIMOUT(output);
}


/*
 * This function returns the compare value currently set for the specified timer.
 */
  uint16_t FLEXIO_GetTimerCompare(const FLEXIO_Type *baseAddr, uint8_t timer)
{
    return (uint16_t)(baseAddr->TIMCMP[timer]);
}


/*
 * This function configures the compare value for the specified timer.
 * The timer compare value is loaded into the timer counter when the timer is first enabled,
 * when the timer is reset and when the timer decrements down to zero.
 * In dual 8-bit counters baud/bit mode, the lower 8-bits configure the baud rate divider
 * and the upper 8-bits configure the number of bits in each word.
 * In dual 8-bit counters PWM mode, the lower 8-bits configure the high period of the output
 * and the upper 8-bits configure the low period.
 * In 16-bit counter mode, the compare value can be used to generate the baud rate divider
 * (if shift clock source is timer output) or the number of bits in each word (when the shift
 * clock source is a pin or trigger input).
 */
  void FLEXIO_SetTimerCompare(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             uint16_t value)
{
    baseAddr->TIMCMP[timer] = (uint32_t)value;
}


/*
 * This function initializes all the registers of the FlexIO module to
 * their reset value.
 */
  void FLEXIO_Init(FLEXIO_Type *baseAddr)
{
    /* Use software reset bit to reset the module */
    FLEXIO_SetSoftwareReset(baseAddr, true);
    /* Control register is not affected by software reset */
    baseAddr->CTRL = 0x0U;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/



