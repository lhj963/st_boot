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

#ifndef FLEXIO_HW_ACCESS_H
#define FLEXIO_HW_ACCESS_H

#include <stdbool.h>
#include "device_registers.h"

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, Expression assigned to a narrower 
 * or different essential type [MISRA 2012 Rule 10.3, required]
 * This is required by the conversion of an unsigned value of a bitfield/bit into an enum value.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, 
 * Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially Boolean'
 * This is required by the efficient conversion of a bit value into a bool for Get functions.
 * Impermissible cast; cannot cast from 'essentially Boolean' to 'essentially unsigned'
 * This is required by the efficient conversion of a bool into a bit value for Set functions.
 * Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum<i>
 * This is required by the efficient conversion of a bit-field value into an enum for Get functions.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.8, Impermissible cast of composite expression 
 *(different essential type categories).
 * This is required by the conversion of a bit/bitfield of a register into boolean or an enum type.
 */

 /*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Shift clock polarity options   */
typedef enum
{
    FLEXIO_TIMER_POLARITY_POSEDGE = 0x00U,     /*!< Shift on positive edge of Shift clock */
    FLEXIO_TIMER_POLARITY_NEGEDGE = 0x01U,     /*!< Shift on negative edge of Shift clock */
} flexio_timer_polarity_t;

/* Pin polarity options   */
typedef enum
{
    FLEXIO_PIN_POLARITY_HIGH = 0x00U,          /*!< Pin is active high */
    FLEXIO_PIN_POLARITY_LOW  = 0x01U,          /*!< Pin is active low  */
} flexio_pin_polarity_t;

/* Pin configuration options   */
typedef enum
{
    FLEXIO_PIN_CONFIG_DISABLED     = 0x00U,    /*!< Shifter pin output disabled */
    FLEXIO_PIN_CONFIG_OPEN_DRAIN   = 0x01U,    /*!< Shifter pin open drain or bidirectional output enable */
    FLEXIO_PIN_CONFIG_BIDIR_OUTPUT = 0x02U,    /*!< Shifter pin bidirectional output data */
    FLEXIO_PIN_CONFIG_OUTPUT       = 0x03U,    /*!< Shifter pin output */
} flexio_pin_config_t;

/* Shifter mode options   */
typedef enum
{
    FLEXIO_SHIFTER_MODE_DISABLED          = 0x00U,  /*!< Shifter disabled */
    FLEXIO_SHIFTER_MODE_RECEIVE           = 0x01U,  /*!< Receive mode */
    FLEXIO_SHIFTER_MODE_TRANSMIT          = 0x02U,  /*!< Transmit mode */
    FLEXIO_SHIFTER_MODE_MATCH_STORE       = 0x04U,  /*!< Match Store mode */
    FLEXIO_SHIFTER_MODE_MATCH_CONTINUOUS  = 0x05U,  /*!< Match Continuous mode */
} flexio_shifter_mode_t;

/* Shifter input source options   */
typedef enum
{
    FLEXIO_SHIFTER_SOURCE_PIN        = 0x00U,  /*!< Input source is selected pin */
    FLEXIO_SHIFTER_SOURCE_SHIFTER    = 0x01U,  /*!< Input source is shifter N+1 output */
} flexio_shifter_source_t;

/* Read/Write mode for shifter buffer   */
typedef enum
{
    FLEXIO_SHIFTER_RW_MODE_NORMAL    = 0x00U,  /*!< Normal shifter buffer read/write */
    FLEXIO_SHIFTER_RW_MODE_BIT_SWAP  = 0x01U,  /*!< Data is bit-swapped */
} flexio_shifter_buffer_mode_t;

/* Trigger polarity   */
typedef enum
{
    FLEXIO_TRIGGER_POLARITY_HIGH = 0x00U,          /*!< Trigger is active high */
    FLEXIO_TRIGGER_POLARITY_LOW  = 0x01U,          /*!< Trigger is active low  */
} flexio_trigger_polarity_t;

/* Trigger sources   */
typedef enum
{
    FLEXIO_TRIGGER_SOURCE_EXTERNAL  = 0x00U,  /*!< External trigger selected */
    FLEXIO_TRIGGER_SOURCE_INTERNAL  = 0x01U,  /*!< Internal trigger selected */
} flexio_trigger_source_t;

/* Timer mode options   */
typedef enum
{
    FLEXIO_TIMER_MODE_DISABLED    = 0x00U,  /*!< Timer Disabled. */
    FLEXIO_TIMER_MODE_8BIT_BAUD   = 0x01U,  /*!< Dual 8-bit counters baud/bit mode. */
    FLEXIO_TIMER_MODE_8BIT_PWM    = 0x02U,  /*!< Dual 8-bit counters PWM mode. */
    FLEXIO_TIMER_MODE_16BIT       = 0x03U,  /*!< Single 16-bit counter mode. */
} flexio_timer_mode_t;

/* Timer initial output options   */
typedef enum
{
    FLEXIO_TIMER_INITOUT_ONE          = 0x00U,  /*!< Timer output is logic one when enabled, unaffected by timer reset. */
    FLEXIO_TIMER_INITOUT_ZERO         = 0x01U,  /*!< Timer output is logic zero when enabled, unaffected by timer reset. */
    FLEXIO_TIMER_INITOUT_ONE_RESET    = 0x02U,  /*!< Timer output is logic one when enabled and on timer reset. */
    FLEXIO_TIMER_INITOUT_ZERO_RESET   = 0x03U,  /*!< Timer output is logic zero when enabled and on timer reset. */
} flexio_timer_output_t;

/* Timer decrement options   */
typedef enum
{
    FLEXIO_TIMER_DECREMENT_CLK_SHIFT_TMR      = 0x00U,  /*!< Decrement counter on FlexIO clock, Shift clock equals Timer output. */
    FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TMR      = 0x01U,  /*!< Decrement counter on Trigger input (both edges), Shift clock equals Timer output. */
    FLEXIO_TIMER_DECREMENT_PIN_SHIFT_PIN      = 0x02U,  /*!< Decrement counter on Pin input (both edges), Shift clock equals Pin input. */
    FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TRG      = 0x03U,  /*!< Decrement counter on Trigger input (both edges), Shift clock equals Trigger input. */
} flexio_timer_decrement_t;

/* Timer reset options   */
typedef enum
{
    FLEXIO_TIMER_RESET_NEVER                  = 0x00U,  /*!< Timer never reset. */
    FLEXIO_TIMER_RESET_PIN_OUT                = 0x02U,  /*!< Timer reset on Timer Pin equal to Timer Output. */
    FLEXIO_TIMER_RESET_TRG_OUT                = 0x03U,  /*!< Timer reset on Timer Trigger equal to Timer Output. */
    FLEXIO_TIMER_RESET_PIN_RISING             = 0x04U,  /*!< Timer reset on Timer Pin rising edge. */
    FLEXIO_TIMER_RESET_TRG_RISING             = 0x06U,  /*!< Timer reset on Trigger rising edge. */
    FLEXIO_TIMER_RESET_TRG_BOTH               = 0x07U,  /*!< Timer reset on Trigger rising or falling edge. */
} flexio_timer_reset_t;

/* Timer disable options   */
typedef enum
{
    FLEXIO_TIMER_DISABLE_NEVER                = 0x00U,  /*!< Timer never disabled. */
    FLEXIO_TIMER_DISABLE_TIM_DISABLE          = 0x01U,  /*!< Timer disabled on Timer N-1 disable. */
    FLEXIO_TIMER_DISABLE_TIM_CMP              = 0x02U,  /*!< Timer disabled on Timer compare. */
    FLEXIO_TIMER_DISABLE_TIM_CMP_TRG_LOW      = 0x03U,  /*!< Timer disabled on Timer compare and Trigger Low. */
    FLEXIO_TIMER_DISABLE_PIN                  = 0x04U,  /*!< Timer disabled on Pin rising or falling edge. */
    FLEXIO_TIMER_DISABLE_PIN_TRG_HIGH         = 0x05U,  /*!< Timer disabled on Pin rising or falling edge provided Trigger is high. */
    FLEXIO_TIMER_DISABLE_TRG                  = 0x06U,  /*!< Timer disabled on Trigger falling edge. */
} flexio_timer_disable_t;

/* Timer disable options   */
typedef enum
{
    FLEXIO_TIMER_ENABLE_ALWAYS                  = 0x00U,  /*!< Timer always enabled. */
    FLEXIO_TIMER_ENABLE_TIM_ENABLE              = 0x01U,  /*!< Timer enabled on Timer N-1 enable. */
    FLEXIO_TIMER_ENABLE_TRG_HIGH                = 0x02U,  /*!< Timer enabled on Trigger high. */
    FLEXIO_TIMER_ENABLE_TRG_PIN_HIGH            = 0x03U,  /*!< Timer enabled on Trigger high and Pin high. */
    FLEXIO_TIMER_ENABLE_PIN_POSEDGE             = 0x04U,  /*!< Timer enabled on Pin rising edge. */
    FLEXIO_TIMER_ENABLE_PIN_POSEDGE_TRG_HIGH    = 0x05U,  /*!< Timer enabled on Pin rising edge and Trigger high. */
    FLEXIO_TIMER_ENABLE_TRG_POSEDGE             = 0x06U,  /*!< Timer enabled on Trigger rising edge. */
    FLEXIO_TIMER_ENABLE_TRG_EDGE                = 0x07U,  /*!< Timer enabled on Trigger rising or falling edge. */
} flexio_timer_enable_t;

/* Timer stop bit options   */
typedef enum
{
    FLEXIO_TIMER_STOP_BIT_DISABLED              = 0x00U,  /*!< Stop bit disabled. */
    FLEXIO_TIMER_STOP_BIT_TIM_CMP               = 0x01U,  /*!< Stop bit is enabled on timer compare. */
    FLEXIO_TIMER_STOP_BIT_TIM_DIS               = 0x02U,  /*!< Stop bit is enabled on timer disable. */
    FLEXIO_TIMER_STOP_BIT_TIM_CMP_DIS           = 0x03U,  /*!< Stop bit is enabled on timer compare and disable. */
} flexio_timer_stop_t;

/* Timer stop bit options - for Transmit, Receive or Match Store modes only   */
typedef enum
{
    FLEXIO_SHIFTER_STOP_BIT_DISABLED            = 0x00U,  /*!< Stop bit disabled. */
    FLEXIO_SHIFTER_STOP_BIT_0                   = 0x02U,  /*!< Transmit/expect stop bit value 0 */
    FLEXIO_SHIFTER_STOP_BIT_1                   = 0x03U,  /*!< Transmit/expect stop bit value 1 */
} flexio_shifter_stop_t;

/* Timer start bit options - for Transmit, Receive or Match Store modes only   */
typedef enum
{
    FLEXIO_SHIFTER_START_BIT_DISABLED       = 0x00U,  /*!< Start bit disabled, transmitter loads data on enable */
    FLEXIO_SHIFTER_START_BIT_DISABLED_SH    = 0x01U,  /*!< Start bit disabled, transmitter loads data on first shift */
    FLEXIO_SHIFTER_START_BIT_0              = 0x02U,  /*!< Transmit/expect start bit value 0 */
    FLEXIO_SHIFTER_START_BIT_1              = 0x03U,  /*!< Transmit/expect start bit value 1 */
} flexio_shifter_start_t;

/* Timer start bit options   */
typedef enum
{
    FLEXIO_TIMER_START_BIT_DISABLED              = 0x00U,  /*!< Start bit disabled. */
    FLEXIO_TIMER_START_BIT_ENABLED               = 0x01U,  /*!< Start bit enabled. */
} flexio_timer_start_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*
 * This function returns the number of shifters of the FlexIO module
 */
extern  uint8_t FLEXIO_GetShifterNum(const FLEXIO_Type *baseAddr);


/*
 * This function enables of disables FlexIO functionality in debug mode.
 */
extern  void FLEXIO_SetDebugMode(FLEXIO_Type *baseAddr, bool enable);


/*
 * Calling this function with enable parameter set to true resets all internal
 * master logic and registers, except the FlexIO Control Register. The reset state
 * persists until this function is called with enable parameter set to false.
 */
extern  void FLEXIO_SetSoftwareReset(FLEXIO_Type *baseAddr, bool enable);


/*
 * This function enables or disables the FlexIO module.
 */
extern  void FLEXIO_SetEnable(FLEXIO_Type *baseAddr, bool enable);

/*
 * This function returns the data read from all the FLEXIO pins. Only the lower
 * n bits are valid, where n is the number of pins returned by FLEXIO_GetPinNum().
 */
extern  uint8_t FLEXIO_GetPinData(const FLEXIO_Type *baseAddr);


/*
 * This function returns the value of the status flag for the specified shifter.
 * The meaning of the status flag depends on the current mode.
 *  - Transmit mode: shifter buffer is empty and ready to accept more data
 *  - Receive mode: shifter buffer is full and received data can be read from it
 *  - Match Store mode: match occurred between shifter buffer and shifter
 *  - Match Continuous mode: current match result between shifter buffer and shifter
 */
extern  bool FLEXIO_GetShifterStatus(const FLEXIO_Type *baseAddr, uint8_t shifter);


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
extern  uint32_t FLEXIO_GetAllShifterStatus(const FLEXIO_Type *baseAddr);

/*
 * This function clears the status flag for the specified shifter. This is possible in
 * all modes except Match Continuous mode.
 */
extern  void FLEXIO_ClearShifterStatus(FLEXIO_Type *baseAddr, uint8_t shifter);


/*
 * This function returns the value of the error status flag for the specified shifter.
 * The meaning of the error status flag depends on the current mode.
 *  - Transmit mode: shifter buffer was not written before it was transferred in the shifter (buffer overrun)
 *  - Receive mode: shifter buffer was not read before new data was transferred from the shifter (buffer underrun)
 *  - Match Store mode: match event occurred before the previous match data was read from shifter buffer (buffer overrun)
 *  - Match Continuous mode: match occurred between shifter buffer and shifter
 */
extern  bool FLEXIO_GetShifterErrorStatus(const FLEXIO_Type *baseAddr, uint8_t shifter);


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
extern  uint32_t FLEXIO_GetAllShifterErrorStatus(const FLEXIO_Type *baseAddr);


/*
 * This function clears the error status flag for the specified shifter.
 */
extern  void FLEXIO_ClearShifterErrorStatus(FLEXIO_Type *baseAddr, uint8_t shifter);


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
extern  bool FLEXIO_GetTimerStatus(const FLEXIO_Type *baseAddr, uint8_t timer);



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
extern  uint32_t FLEXIO_GetAllTimerStatus(const FLEXIO_Type *baseAddr);

/*
 * This function clears the status flag for the specified timer.
 */
extern  void FLEXIO_ClearTimerStatus(FLEXIO_Type *baseAddr, uint8_t timer);


/*
 * Returns the state of the interrupt for all shifters. Each bit in 
 * the returned value specifies the interrupt state for one shifter, starting with 
 * shifter 0 from least significant bit.
 */
extern  uint32_t FLEXIO_GetAllShifterInterrupt(const FLEXIO_Type *baseAddr);


/*
 * Enable or disable specified shifter interrupts. The interrupt mask must contain a
 * bit of 1 for each shifter who's interrupt must be enabled or disabled.
 */
extern  void FLEXIO_SetShifterInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable);



/*
 * Returns the state of the error interrupt for all shifters. Each bit in 
 * the returned value specifies the interrupt state for one shifter, starting with 
 * shifter 0 from least significant bit.
 */
extern  uint32_t FLEXIO_GetAllShifterErrorInterrupt(const FLEXIO_Type *baseAddr);


/*
 * Enable or disable specified shifter error interrupts. The interrupt mask must contain a
 * bit of 1 for each shifter who's error interrupt must be enabled or disabled.
 */
extern  void FLEXIO_SetShifterErrorInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable);

/*
 * Returns the state of the interrupt for all timers. Each bit in 
 * the returned value specifies the interrupt state for one timer, starting with 
 * timer 0 from least significant bit.
 */
extern  uint32_t FLEXIO_GetAllTimerInterrupt(const FLEXIO_Type *baseAddr);


/*
 * Enable or disable specified timer interrupts. The interrupt mask must contain a
 * bit of 1 for each timer who's interrupt must be enabled or disabled.
 */
extern  void FLEXIO_SetTimerInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable);


/*
 * Enable or disable specified shifter DMA requests. The request mask must contain a
 * bit of 1 for each shifter who's DMA requests must be enabled or disabled.
 */
extern  void FLEXIO_SetShifterDMARequest(FLEXIO_Type *baseAddr, uint8_t requestMask, bool enable);



/*
 * This function assigns a timer to control the specified shifter, and also configures its polarity.
 */
extern  void FLEXIO_SetShifterTimer(FLEXIO_Type *baseAddr,
                                              uint8_t shifter,
                                              uint8_t timer,
                                              flexio_timer_polarity_t polarity);


/*
 * This function assigns the specified pin to the specified shifter, and also sets
 * its polarity and configuration.
 */
extern  void FLEXIO_SetShifterPin(FLEXIO_Type *baseAddr,
                                            uint8_t shifter,
                                            uint8_t pin,
                                            flexio_pin_polarity_t polarity,
                                            flexio_pin_config_t config);

/*
 * This function configures the pin assigned to the specified specified shifter. 
 * It does not change the other pin-related settings.
 */
extern  void FLEXIO_SetShifterPinConfig(FLEXIO_Type *baseAddr,
                                                  uint8_t shifter,
                                                  flexio_pin_config_t config);
/*
 * This function configures the mode for the specified shifter.
 */
extern  void FLEXIO_SetShifterMode(FLEXIO_Type *baseAddr,
                                             uint8_t shifter,
                                             flexio_shifter_mode_t mode);

/*
 * This function configures the control settings for the specified shifter: mode settings, 
 * pin settings and timer settings.
 */
extern  void FLEXIO_SetShifterControl(FLEXIO_Type *baseAddr,
                                                uint8_t shifter,
                                                flexio_shifter_mode_t mode,
                                                uint8_t pin,
                                                flexio_pin_polarity_t pinPolarity,
                                                flexio_pin_config_t pinConfig,
                                                uint8_t timer,
                                                flexio_timer_polarity_t timerPolarity);

/*
 * This function configures the input source of the specified shifter.
 */
extern  void FLEXIO_SetShifterInputSource(FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_source_t source);

/*
 * This function configures the sending or receiving of
 * a stop bit in Transmit, Receive or Match Store modes.
 */
extern  void FLEXIO_SetShifterStopBit(FLEXIO_Type *baseAddr, uint8_t shifter, flexio_shifter_stop_t stop);


/*
 * This function configures the sending or receiving of
 * a start bit in Transmit, Receive or Match Store modes.
 */
extern  void FLEXIO_SetShifterStartBit(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 flexio_shifter_start_t start);

/*
 * This function sets the following configurations for the specified shifter:
 * start bit, stop bit, input source
 */
extern  void FLEXIO_SetShifterConfig(FLEXIO_Type *baseAddr,
                                               uint8_t shifter,
                                               flexio_shifter_start_t start,
                                               flexio_shifter_stop_t stop,
                                               flexio_shifter_source_t source);

/*
 * This function reads data from the specified shifter buffer. The data can be
 * read in any of the four ways allowed by the hardware - see description of type
 * flexio_shifter_buffer_mode_t for details.
 */
extern  uint32_t FLEXIO_ReadShifterBuffer(const FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_buffer_mode_t mode);
/*
 * This function writes data in the specified shifter buffer. The data can be
 * written in any of the four ways allowed by the hardware - see description of type
 * flexio_shifter_buffer_mode_t for details.
 */
extern  void FLEXIO_WriteShifterBuffer(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 uint32_t value,
                                                 flexio_shifter_buffer_mode_t mode);


/*
 * This function configures the trigger for the specified timer, and also its
 * source (internal or external) and polarity settings.
 * For internal triggers, the selection is as follows:
 *  - 4*N - Pin 2*N input
 *  - 4*N+1 - Shifter N status flag
 *  - 4*N+2 - Pin 2*N+1 input
 *  - 4*N+3 - Timer N trigger output
 */
extern  void FLEXIO_SetTimerTrigger(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t trigger,
                                                 flexio_trigger_polarity_t polarity,
                                                 flexio_trigger_source_t source);

/*
 * This function assigns the specified pin to the specified timer, and also sets
 * its polarity and configuration.
 */
extern  void FLEXIO_SetTimerPin(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t pin,
                                                 flexio_pin_polarity_t polarity,
                                                 flexio_pin_config_t config);


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
extern  void FLEXIO_SetTimerMode(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_mode_t mode);


/*
 * This function configures the control settings for the specified timer: mode settings, 
 * pin settings and trigger settings.
 */
extern  void FLEXIO_SetTimerControl(FLEXIO_Type *baseAddr,
                                              uint8_t timer,
                                              uint8_t trigger,
                                              flexio_trigger_polarity_t triggerPolarity,
                                              flexio_trigger_source_t triggerSource,
                                              uint8_t pin,
                                              flexio_pin_polarity_t pinPolarity,
                                              flexio_pin_config_t pinConfig,
                                              flexio_timer_mode_t mode);


/*
 * This function configures the initial output of the specified timer and whether it is
 * affected by the Timer reset.
 */
extern  void FLEXIO_SetTimerInitialOutput(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_output_t output);


/*
 * This function configures the decrement condition for the specified timer and the source
 * of the shift clock.
 * See description of type flexio_timer_decrement_t for a list of options.
 */
extern  void FLEXIO_SetTimerDecrement(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_decrement_t decrement);


/*
 * This function configures the conditions that cause the timer counter (and optionally
 * output) to be reset. In 8-bit counter mode, the timer reset will only reset the
 * lower 8-bits that configure the baud rate. In all other modes, the timer reset
 * will reset the full 16-bits of the counter.
 * See description of type flexio_timer_decrement_t for a list of options.
 */
extern  void FLEXIO_SetTimerReset(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_reset_t reset);

/*
 * This function configures the condition that cause the specified timer to be disabled.
 * See description of type flexio_timer_disable_t for a list of options.
 */
extern  void FLEXIO_SetTimerDisable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_disable_t disable);

/*
 * This function configures the condition that cause the specified timer to be enabled
 * and start decrementing.
 * See description of type flexio_timer_disable_t for a list of options.
 */
extern  void FLEXIO_SetTimerEnable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_enable_t enable);

/*
 * This function configures stop bit insertion for the specified timer.
 * The stop bit can be added on a timer compare (between each word) or on a timer disable.
 * When stop bit is enabled, configured shifters will output the contents of the stop bit
 * when the timer is disabled. When stop bit is enabled on timer disable, the timer remains
 * disabled until the next rising edge of the shift clock. If configured for both timer
 * compare and timer disable, only one stop bit is inserted on timer disable.
 */
extern  void FLEXIO_SetTimerStop(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_stop_t stop);


/*
 * This function configures start bit insertion for the specified timer.
 * When start bit is enabled, configured shifters will output the contents of the start
 * bit when the timer is enabled and the timer counter will reload from the compare
 * register on the first rising edge of the shift clock.
 */
extern  void FLEXIO_SetTimerStart(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start);

/*
 * This function sets the following configurations for the specified timer:
 * start bit, stop bit, enable condition, disable condition, reset condition, 
 * decrement condition, initial output
 */
extern  void FLEXIO_SetTimerConfig(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start,
                                             flexio_timer_stop_t stop,
                                             flexio_timer_enable_t enable,
                                             flexio_timer_disable_t disable,
                                             flexio_timer_reset_t reset,
                                             flexio_timer_decrement_t decrement,
                                             flexio_timer_output_t output);


/*
 * This function returns the compare value currently set for the specified timer.
 */
extern  uint16_t FLEXIO_GetTimerCompare(const FLEXIO_Type *baseAddr, uint8_t timer);

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
extern  void FLEXIO_SetTimerCompare(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             uint16_t value);

/*
 * This function initializes all the registers of the FlexIO module to
 * their reset value.
 */
extern  void FLEXIO_Init(FLEXIO_Type *baseAddr);

#if defined(__cplusplus)
}
#endif

#endif /* FLEXIO_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/


